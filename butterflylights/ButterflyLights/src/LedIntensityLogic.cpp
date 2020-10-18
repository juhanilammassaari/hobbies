#include <Arduino.h>
#include "LedConfig.h"
#include "LedIntensityLogic.h"

void set_led(const int8_t red, const int8_t green, const int8_t blue)
{
    analogWrite(PIN_LED_RED, red);
    analogWrite(PIN_LED_GREEN, green);
    analogWrite(PIN_LED_BLUE, blue);
}