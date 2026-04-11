#ifndef MOTION_H
#define MOTION_H

// MOTION SENSOR PIN
#define PIR_PIN 2

// Time in milliseconds to consider the area unoccupied after last motion detected (15 seconds)
#define ABSENCE_TIMEOUT_MS 15000 

extern int lastMotionTime; // Timestamp of the last detected motion
extern bool occupied; // Flag to track if the area is currently occupied

void notifyMotionDetected(int now);
void notifyNoMotion(int now);
int simulatePIR();
void handleMotionSensor(bool simulationMode, int now);


#endif // MOTION_H