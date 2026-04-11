#include "water.h"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>

// ===== ALERTS =====
void triggerAlarm_Water() {
    Serial.printf("[WATER SENSOR] FLOOD ALERT %d\n", millis());

    //TO DO: SEND ALERT TO AZURE OR OTHER CLOUD SERVICE
    //TO DO: ADD LED ALERT
}

void handleWaterSensor(bool simulationMode) {
    //jeżeli stan wody jest niski (0) to wysyła alert o zalaniu
        digitalWrite(WATER_OUT_PIN, HIGH);
        int waterState = digitalRead(WATER_IN_PIN);

        Serial.printf("[WATER] %d\n", waterState);

        if (waterState == 0) {
            triggerAlarm_Water();
        }
}
