import { PermissionsAndroid } from 'react-native';

export default class BlePermissions {

  static requestPermission = async () => {
    try {
      const granted = await PermissionsAndroid.request(
        PermissionsAndroid.PERMISSIONS.ACCESS_COARSE_LOCATION,
        {
          title: 'BLE coarse location permission',
          message: 'Need permission',
          buttonNeutral: 'Ask Me Later',
          buttonNegative: 'Cancel',
          buttonPositive: 'OK',
        },
      );
      if (granted === PermissionsAndroid.RESULTS.GRANTED) {
        console.log('ACCESS_COARSE_LOCATION allowed');
        return true;
      }

      console.log('ACCESS_COARSE_LOCATION denied');
    } catch (err) {
      console.warn(err);
    }

    return false;
  };

}