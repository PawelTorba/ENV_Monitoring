#include "motion.h"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>

int lastMotionTime = 0; // Timestamp of the last detected motion
bool occupied = false; // Flag to track if the area is currently occupied

    // LOGIKA PIR:
    // Jeżeli wykryje ruch to ustawia flagę occupied na true i wysyła alert. 
    // Jeżeli nie wykryje ruchu przez określony czas (ABSENCE_TIMEOUT_MS) to ustawia occupied na false i wysyła alert o braku ruchu.

int simulatePIR() {
    return (rand() % 10) < 1; // 10% chance of detecting motion
}

void notifyMotionDetected(int now) {
    char payload[256];
    snprintf(payload, sizeof(payload),
    "{\"sensorType\":\"motion\",\"timestamp\":%d,\"alert\":%s}",
    now, "true");
    
    Serial.printf("[MOTION] Payload: %s\r\n", payload);
    //TO DO: SEND ALERT TO AZURE OR OTHER CLOUD SERVICE
    //TO DO: ADD LED ALERT
}

void notifyNoMotion(int now) {
    //Serial.printf("[MOTION SENSOR] NO MOVEMENT %d\n", millis());
    char payload[256];
    snprintf(payload, sizeof(payload),
    "{\"sensorType\":\"motion\",\"timestamp\":%d,\"alert\":%s}",
    now, "false");  
    Serial.printf("[MOTION] Payload: %s\r\n", payload);
    //TO DO: SEND ALERT TO AZURE OR OTHER CLOUD SERVICE
}

void handleMotionSensor(bool simulationMode, int now) {
    int pir = simulationMode ? simulatePIR() : digitalRead(PIR_PIN);

    if (pir == 1) {
        lastMotionTime = now;

        if (!occupied) {
            occupied = true;
            notifyMotionDetected(now);
        }
    } else {
        if (occupied && (now - lastMotionTime > ABSENCE_TIMEOUT_MS)) {
            occupied = false;
            notifyNoMotion(now);
        }
    }
}

