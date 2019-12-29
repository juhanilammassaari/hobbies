/*
 Name:		GingerbreadChip.ino
 Created:	12/17/2019 9:13:01 PM
 Author:	Juhani Lammassaari
*/

#include <Arduino.h>
#include "src/Ble.h"
#include "src/LedConfig.h"

#define LED_FREQUENCY (5000)
#define LED_RESOLUTION (8)

Ble ble;
unsigned char previousRed = 0;
unsigned char previousGreen = 0;
unsigned char previousBlue = 0;

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(115200);
    
    Serial.println("Setting pins");
    
    ledcSetup(LED_CHANNEL_RED, LED_FREQUENCY, LED_RESOLUTION);
    ledcSetup(LED_CHANNEL_GREEN, LED_FREQUENCY, LED_RESOLUTION);
    ledcSetup(LED_CHANNEL_BLUE, LED_FREQUENCY, LED_RESOLUTION);

    ledcAttachPin(PIN_LED_RED, LED_CHANNEL_RED);
    ledcAttachPin(PIN_LED_GREEN, LED_CHANNEL_GREEN);
    ledcAttachPin(PIN_LED_BLUE, LED_CHANNEL_BLUE);

    //pinMode(pinLedRed, OUTPUT);
    //pinMode(pinLedGreen, OUTPUT);
    //pinMode(pinLedBlue, OUTPUT);

    Serial.println("Starting BLE work");
    ble.Setup();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
    BleCharacteristicsLed* ledCharacteristic = ble.getLedCharacteristic();
    unsigned char red, green, blue;

    ledCharacteristic->GetColorWithVariation(red, green, blue);

    if (previousRed == red && previousGreen == green && previousBlue == blue) 
    {
        delay(100);
        return;
    }

    ledcWrite(LED_CHANNEL_RED, red);
    ledcWrite(LED_CHANNEL_GREEN, green);
    ledcWrite(LED_CHANNEL_BLUE, blue);

    previousRed = red;
    previousGreen = green;
    previousBlue = blue;
    delay(20);
}
