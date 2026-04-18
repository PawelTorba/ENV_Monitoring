#ifndef MOTION_H
#define MOTION_H

#define PIR_PIN 2

#define ABSENCE_TIMEOUT_MS 15000 

extern int lastMotionTime; 
extern bool occupied; 

void notifyMotionDetected(int now);
void notifyNoMotion(int now);
int simulatePIR();
void handleMotionSensor(bool simulationMode, int now);


#endif // MOTION_H