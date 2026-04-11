#ifndef GAS_H
#define GAS_H

#define GAS_DIGITAL_PIN 12
#define GAS_ANALOG_PIN 34
#define GAS_THRESHOLD 700

int generateFakeGasValue();
void triggerAlarm_Gas(int value);
void handleGasSensor(bool simulationMode);
void handleGasValues(int analogValue, int digitalValue);

#endif // GAS_H