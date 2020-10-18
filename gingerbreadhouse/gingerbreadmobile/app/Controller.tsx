import React, { Component } from "react";
import { View, Text, ActivityIndicator, StyleSheet } from 'react-native';
import { Device } from "react-native-ble-plx";
import { ColorPicker, HsvColor, fromHsv, toHsv } from 'react-native-color-picker'
import Slider from '@react-native-community/slider';
import BleApi from './BleApi';
import BlePermission from "./BlePermisson";
import Constants from "./Constants";

const DEFAULT_LED_COLOR = toHsv('red');

const localStyles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#101010'
  },
  title: {
    fontSize: 24,
    fontWeight: 'normal',
    color: '#bbbbbb'
  },
});

export default class Controller extends Component {
  bleApi: BleApi;
  isSending: boolean;
  sendBufferRed: number;
  sendBufferGreen: number;
  sendBufferBlue: number;

  constructor(props: Readonly<{}>) {
    super(props);

    this.isSending = false;
    this.sendBufferRed = null;
    this.sendBufferGreen = null;
    this.sendBufferBlue = null;
    this.bleApi = new BleApi(this.onGingerbreadHouseScanned);

    this.state = {
      connectedDevice: null,
      selectedColor: toHsv(DEFAULT_LED_COLOR),
    };

    this.startBleScan();
  }

  startBleScan = async () => {
    const permissionOk = await BlePermission.requestPermission();
    if (permissionOk) {
      this.bleApi.startScan();
    }
  }

  onGingerbreadHouseScanned = async (device: Device) => {
    console.log("House found <3: " + device.name);
    console.log("Just connecting to it (and stopping scan) <3");

    this.bleApi.stopScan();

    const funcToConnect = async () => {
      const connDevice = await this.bleApi.connectTo(device, Constants.getConnectTimeout());
      if (null === connDevice) {
        console.log("Connect failed. Starting BLE scan again");
        this.bleApi.startScan();
        return;
      }

      console.log("Entered gingerbread house. Sweet!");
      this.setState({
        connectedDevice: connDevice
      });
    }

    setTimeout(funcToConnect, 250); // Detaching the scanned event handler from actual connect attempt.
  }

  onSelectedColorChanged = async (hsvColor: HsvColor) => {
    const colorStr = fromHsv(hsvColor);
    const red = parseInt(colorStr.substr(1, 2), 16);
    const green = parseInt(colorStr.substr(3, 2), 16);
    const blue = parseInt(colorStr.substr(5, 2), 16);

    this.setState({ selectedColor: hsvColor });

    if (true === this.isSending) { // If we are currently sending, store new values to "buffer" to be sent when previous send finishes.
      this.sendBufferRed = red;
      this.sendBufferGreen = green;
      this.sendBufferBlue = blue;
      return;
    }

    this.isSending = true;
    this.sendBufferRed = null;
    this.sendBufferGreen = null;
    this.sendBufferBlue = null;

    this.sendColorFunc(red, green, blue);
  }

  sendColorFunc = async (red: number, green: number, blue: number) => {
    const { connectedDevice } = this.state;
    await this.bleApi.sendColor(connectedDevice.id, red, green, blue);

    if (null === this.sendBufferRed) {
      this.isSending = false;
      return;
    }

    // We have next value in "send buffer". Send it.
    setTimeout(
      () => {
        const redFromBuf = this.sendBufferRed;
        const greenFromBuf = this.sendBufferGreen;
        const blueFromBuf = this.sendBufferBlue;
        this.sendBufferRed = null;
        this.sendBufferGreen = null;
        this.sendBufferBlue = null;
        this.sendColorFunc(redFromBuf, greenFromBuf, blueFromBuf);
      },
      0);
  }

  render() {
    const { connectedDevice, selectedColor } = this.state;

    let content = null;

    if (null === connectedDevice) {
      content = (
        <View style={localStyles.container}>
          <Text style={localStyles.title}>Connecting...</Text>
          <ActivityIndicator />
        </View>
      );
    }
    else {
      content = (
        <View style={localStyles.container}>
          <Text style={localStyles.title}>
            {"Connected to gingerbread house " + connectedDevice.id}
          </Text>
          <ColorPicker
            color={selectedColor}
            defaultColor={DEFAULT_LED_COLOR}
            onColorSelected={this.onSelectedColorChanged}
            onColorChange={this.onSelectedColorChanged}
            style={{flex: 1}}
            hideSliders={false}
          />
        </View>
      );
    }

    return content;
  }
}