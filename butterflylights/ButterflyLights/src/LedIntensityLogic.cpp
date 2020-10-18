#include <Arduino.h>
#include "LedConfig.h"
#include "LedIntensityLogic.h"

#define LED_RED_PROGRAM_LENGTH_MS (25000)
#define LED_GREEN_PROGRAM_LENGTH_MS (37000)
#define LED_BLUE_PROGRAM_LENGTH_MS (31000)

const int led_program_times[] = { 
    LED_RED_PROGRAM_LENGTH_MS, 
    LED_GREEN_PROGRAM_LENGTH_MS, 
    LED_BLUE_PROGRAM_LENGTH_MS 
};

void update_leds(unsigned long timeMs) {
    int led_values[3];
    for (int i = 0; i < 3; ++i) {
        double led_program_time = (timeMs % led_program_times[i]);
        double radians = TWO_PI * (led_program_time / led_program_times[i]);
        led_values[i] = (int8_t)((0.5 + sin(radians) / 2) * UINT8_MAX);
    }

    set_led(led_values[0], led_values[1], led_values[2]);
}

void set_led(const int8_t red, const int8_t green, const int8_t blue)
{
    analogWrite(PIN_LED_RED, red);
    analogWrite(PIN_LED_GREEN, green);
    analogWrite(PIN_LED_BLUE, blue);
}