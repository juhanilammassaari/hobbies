#include "src/LedConfig.h"

void setRgbLed(const int8_t red, const int8_t green, const int8_t blue);

void setup() {
    Serial.begin(115200);
    Serial.println("Setting pins");

    pinMode(PIN_LED_RED, OUTPUT);
    digitalWrite(PIN_LED_RED, LOW);
    pinMode(PIN_LED_GREEN, OUTPUT);
    digitalWrite(PIN_LED_GREEN, LOW);
    pinMode(PIN_LED_BLUE, OUTPUT);
    digitalWrite(PIN_LED_BLUE, LOW);
}

// the loop function runs over and over again forever
void loop() {
    setRgbLed(100, 0, 0);
    delay(1000);              // wait for a second
    setRgbLed(255, 0, 0);
    delay(1000);              // wait for a second
    setRgbLed(0, 255, 0);
    delay(1000);              // wait for a second
    setRgbLed(0, 0, 255);
    delay(1000);              // wait for a second
}

void setRgbLed(const int8_t red, const int8_t green, const int8_t blue)
{
    analogWrite(PIN_LED_RED, red);
    analogWrite(PIN_LED_GREEN, green);
    analogWrite(PIN_LED_BLUE, blue);
}