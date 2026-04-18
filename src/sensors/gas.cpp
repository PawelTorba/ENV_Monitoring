#include "gas.h"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>
#include "azure.h"

// ===== SIMULATION =====
int generateFakeGasValue()  {
    static int gasLevel = 0;
    static int leakTimer = 0;

    if (leakTimer > 0) {
        leakTimer--;
        gasLevel = 300 + rand() % 200; 
        return gasLevel;
    }

    if ((rand() % 200) == 0) {
        leakTimer = 10 + rand() % 20;
    }

    gasLevel = rand() % 50;
    return gasLevel;
}

// ===== ALERTS =====
void triggerAlarm_Gas(int value, int now) {
    //TO DO: ADD LED ALERT
}

void handleGasValues(int analogValue, int digitalValue, int now) {
    // Create JSON payload structure for Azure IoT Hub
    char payload[256];
    snprintf(payload, sizeof(payload),
        "{\"sensorType\":\"gas\",\"analog\":%d,\"digital\":%d,\"timestamp\":%d,\"threshold\":%d,\"alert\":%s}",
        analogValue,
        digitalValue,
        now,
        GAS_THRESHOLD,
        (analogValue > GAS_THRESHOLD || digitalValue == 1) ? "true" : "false"
    );
    
    Serial.printf("[GAS] Payload: %s\r\n", payload);
    
    sendToIoTHub(payload);
}

void handleGasSensor(bool simulationMode, int now) {
    int analogValue;
    int digitalValue;

    if (simulationMode) {
        analogValue = generateFakeGasValue(); // wartość symulowana dla czujnika gazu
        digitalValue = analogValue > GAS_THRESHOLD; // symulacja stanu cyfrowego na podstawie wartości analogowej
    } else {
        analogValue = analogRead(GAS_ANALOG_PIN); // odczyt wartości analogowej z czujnika gazu
        digitalValue = digitalRead(GAS_DIGITAL_PIN); // odczyt stanu cyfrowego z czujnika gazu
    }

    handleGasValues(analogValue, digitalValue, now);
    
}


