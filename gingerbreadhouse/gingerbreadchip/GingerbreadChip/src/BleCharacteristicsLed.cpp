#include <HardwareSerial.h>
#include "BleCharacteristicsLed.h"
#include "ByteManipulation.h"

BleCharacteristicsLed::BleCharacteristicsLed(BLECharacteristic* characteristicWrapped)
	: 
	characteristic(characteristicWrapped)
{
	this->characteristic->setCallbacks(this);
	this->variation.Set(20, 20, 10);
}

BleCharacteristicsLed::~BleCharacteristicsLed()
{
	this->characteristic->setCallbacks(NULL);
}

void BleCharacteristicsLed::onWrite(BLECharacteristic* pCharacteristic)
{
	std::string rxValue = pCharacteristic->getValue();

	Serial.print("Received BLE characteristic write cb:");
	for (int i = 0; i < rxValue.length(); ++i) 
	{
		Serial.print(rxValue[i]);
	}
	Serial.print("\n");

	if (rxValue.length() < 3) 
	{
		Serial.print("Too short data. Dismissing\n");
	}

	this->color.Set(rxValue[2], rxValue[1], rxValue[0]); // in reversed order (BGR)
}

void BleCharacteristicsLed::GetColor(unsigned char& red, unsigned char& green, unsigned char& blue)
{
	this->color.Get(red, green, blue);
}

void BleCharacteristicsLed::GetColorWithVariation(unsigned char& red, unsigned char& green, unsigned char& blue)
{
	int valueRed = this->color.GetRed();
	int valueGreen = this->color.GetGreen();
	int valueBlue = this->color.GetBlue();
	
	unsigned char variationRed = this->variation.GetRed();
	unsigned char variationGreen = this->variation.GetGreen();
	unsigned char variationBlue = this->variation.GetBlue();

	valueRed += (this->GetRandom() % variationRed) - (variationRed / 2);
	valueGreen += (this->GetRandom() % variationGreen) - (variationGreen / 2);
	valueBlue += (this->GetRandom() % variationBlue) - (variationBlue / 2);

	red = ByteManipulation::TruncateToByte(valueRed);
	green = ByteManipulation::TruncateToByte(valueGreen);
	blue = ByteManipulation::TruncateToByte(valueBlue);
}

inline uint32_t BleCharacteristicsLed::GetRandom()
{
	return esp_random();
}
