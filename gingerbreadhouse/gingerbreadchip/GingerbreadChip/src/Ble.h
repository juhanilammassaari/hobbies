#pragma once

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "BleCharacteristicsLed.h"

class Ble {
public:
	Ble();
	virtual ~Ble();
	void Setup();
	BleCharacteristicsLed* getLedCharacteristic();
private:
	BLEServer* pServer;
	BLEService* pService;
	BleCharacteristicsLed* pLedCharacteristic;
	BLEAdvertising* pAdvertising;
};
