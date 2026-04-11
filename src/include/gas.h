#ifndef GAS_H
#define GAS_H

#define GAS_DIGITAL_PIN 12
#define GAS_ANALOG_PIN 34
#define GAS_THRESHOLD 700

int generateFakeGasValue();
void triggerAlarm_Gas(int value, int now);
void handleGasSensor(bool simulationMode, int now);
void handleGasValues(int analogValue, int digitalValue, int now);

#endif // GAS_H