#include "gas.h"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>

// ===== SIMULATION =====
int generateFakeGasValue() {
    return rand() % 1024;
}

// ===== ALERTS =====
void triggerAlarm_Gas(int value) {
    Serial.printf("[GAS SENSOR] GAS ALERT %d\n", value);
    //TO DO: SEND ALERT TO AZURE OR OTHER CLOUD SERVICE
    //TO DO: ADD LED ALERT

}

void handleGasValues(int analogValue, int digitalValue) {
    Serial.printf("[GAS] Analog: %d | Digital: %d\n", analogValue, digitalValue);

    //TO DO: SEND DATA TO AZURE OR OTHER CLOUD SERVICE
}

void handleGasSensor(bool simulationMode) {
    int analogValue;
    int digitalValue;

    if (simulationMode) {
        analogValue = generateFakeGasValue(); // wartość symulowana dla czujnika gazu
        digitalValue = analogValue > GAS_THRESHOLD; // symulacja stanu cyfrowego na podstawie wartości analogowej
    } else {
        analogValue = analogRead(GAS_ANALOG_PIN); // odczyt wartości analogowej z czujnika gazu
        digitalValue = digitalRead(GAS_DIGITAL_PIN); // odczyt stanu cyfrowego z czujnika gazu
    }

    handleGasValues(analogValue, digitalValue);

    //HANDLE POTENTIAL ALERTS
    if (analogValue > GAS_THRESHOLD || digitalValue == 1) {
        triggerAlarm_Gas(analogValue);
    }
}


