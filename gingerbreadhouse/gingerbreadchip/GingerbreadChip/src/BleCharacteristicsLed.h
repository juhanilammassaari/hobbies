#pragma once

#include <BLECharacteristic.h>
#include "Color.h"

class BleCharacteristicsLed : public BLECharacteristicCallbacks
{
public:
	BleCharacteristicsLed(BLECharacteristic * characteristicWrapped);
	virtual ~BleCharacteristicsLed();
	virtual void GetColor(unsigned char &red, unsigned char& green, unsigned char& blue);
	virtual void GetColorWithVariation(unsigned char& red, unsigned char& green, unsigned char& blue);
	
protected:
	virtual void onWrite(BLECharacteristic* pCharacteristic);
	virtual uint32_t GetRandom();
	

private:
	BLECharacteristic* characteristic;
	Color color;
	Color variation;
};