#include "src/LedConfig.h"
#include "src/LedIntensityLogic.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Setting pins");

    configure_leds();
}

// the loop function runs over and over again forever
void loop() {
    set_led(100, 0, 0);
    delay(1000);              // wait for a second
    set_led(255, 0, 0);
    delay(1000);              // wait for a second
    set_led(0, 255, 0);
    delay(1000);              // wait for a second
    set_led(0, 0, 255);
    delay(1000);              // wait for a second
}

