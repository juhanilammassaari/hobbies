import { BleManager, BleError, Device } from 'react-native-ble-plx';
import { Buffer } from 'buffer'

const serviceUuid = "017353b6-9303-4d9a-b4a2-470971bfe049";
const characteristicUuid = "71fcc424-f36d-44c3-a8cc-8d94d2bb6fcb";
const deviceName = "Gingerbread house";
const bleManagerRestoreStateIdentifier = "a69e4f9b-3c83-4a60-9acc-b06b7042180a";

export default class BleApi {
  bleManager: BleManager;
  onGingerbreadHouseScanned: (device: Device) => void;

  static toBase64(arr: any) {
    return new Buffer(arr).toString("base64");
  }

  constructor(onGingerbreadHouseScanned: (device: Device) => void) {
    this.bleManager = this.createBleManager();
    this.onGingerbreadHouseScanned = onGingerbreadHouseScanned;
  }

  /**
   * Tries to connect to given BLE device.
   * @param device Device to connect.
   * @param timeoutMs Connect timeout in milliseconds.
   * @returns Device or null depending if connect was successful.
   */
  connectTo = async (device: Device, timeoutMs: number) => {
    if (null === device || undefined === device) {
      return null;
    }

    const connectionOptions = (undefined !== timeoutMs && null !== timeoutMs)
      ? {  timeout: timeoutMs }
      : undefined;

    console.log("BLE manager tries to connect to device: " + device.id);
    const connectedDevice = await this.bleManager.connectToDevice(device.id, connectionOptions);

    if (null === connectedDevice) {
      console.log("Connect failed");
      return null;
    }

    console.log("Discovering services and characteristics");
    return await this.bleManager.discoverAllServicesAndCharacteristicsForDevice(connectedDevice.id, undefined);
  }

  sendColor = async (deviceId: string, r: number, g: number, b: number) => {
    const base64Data = BleApi.toBase64([r & 0xFF, g & 0xFF, b & 0xFF]);
    console.log("Sending rgb: " + r + ", " + g + ", " + b + " => " + base64Data);
    this.bleManager.writeCharacteristicWithResponseForDevice(deviceId, serviceUuid, characteristicUuid, base64Data , undefined);
  }

  /**
   * Creates the BLE manager object provided by react-native-ble-plx.
   */
  createBleManager = () => {
    const restoreStateOptions = { // type: BleManagerOptions
      restoreStateIdentifier: bleManagerRestoreStateIdentifier,
    };
    const bleManager = new BleManager(restoreStateOptions);
    return bleManager;
  }

  onDeviceScannedHandler = (error: BleError, device: Device) => {
    if (error) {
      console.log("Device scan error occurred: " + error);
    }

    if (!device || deviceName !== device.name) {
      return;
    }

    if (!this.onGingerbreadHouseScanned) {
      console.log("Gingerbread house found, but no callback function defined");
      return;
    }

    this.onGingerbreadHouseScanned(device);
  }

  /**
   * Starts to scan for gingerbreadhouses.
   * When found predefined callback function is invoked.
   */
  startScan = () => {
    const scanOptions = {
      allowDuplicates: true,
    };
    this.bleManager.startDeviceScan([serviceUuid], scanOptions, this.onDeviceScannedHandler);
  }

  stopScan = () => {
    this.bleManager.stopDeviceScan();
  }
}
