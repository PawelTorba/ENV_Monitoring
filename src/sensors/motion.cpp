#include "motion.h"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>
#include "azure.h"

int lastMotionTime = 0; 
bool occupied = false; 

int simulatePIR() {
    static int motionState = 0;
    static int motionTimer = 0;

    if (motionState == 1) {
        motionTimer--;
        if (motionTimer <= 0) motionState = 0;
        return 1;
    }

    if ((rand() % 100) < 2) { 
        motionState = 1;
        motionTimer = 5 + rand() % 10;
        return 1;
    }

    return 0;
}

void notifyMotionDetected(int now) {
    char payload[256];
    snprintf(payload, sizeof(payload),
    "{\"sensorType\":\"motion\",\"timestamp\":%d,\"alert\":%s}",
    now, "true");
    
    Serial.printf("[MOTION] Payload: %s\r\n", payload);
    sendToIoTHub(payload);
}

void notifyNoMotion(int now) {
    char payload[256];
    snprintf(payload, sizeof(payload),
    "{\"sensorType\":\"motion\",\"timestamp\":%d,\"alert\":%s}",
    now, "false");  
    Serial.printf("[MOTION] Payload: %s\r\n", payload);

    sendToIoTHub(payload);
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

