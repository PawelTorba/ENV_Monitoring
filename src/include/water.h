#ifndef WATER_H
#define WATER_H

#define WATER_OUT_PIN 25
#define WATER_IN_PIN  26

void triggerAlarm_Water(int now);
void handleWaterSensor(bool simulationMode, int now);

#endif