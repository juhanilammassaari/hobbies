#include "src/LedConfig.h"
#include "src/LedIntensityLogic.h"

#define POWER_SAVE_SLEEP_TIME_MS 15

void setup() {
    Serial.begin(115200);
    Serial.println("Setting pins");

    configure_leds();
}

void loop() {
    unsigned long currentTime = millis();
    update_leds(currentTime);
    delay(POWER_SAVE_SLEEP_TIME_MS);
}

