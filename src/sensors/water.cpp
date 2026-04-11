#include "water.h"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>
#include "azure.h"

// ===== ALERTS =====
void triggerAlarm_Water(int now) {
    //TO DO: ADD LED ALERT
    //TO DO: SEND payload TO AZURE IOT HUB
}



void handleWaterSensor(bool simulationMode, int now) {
    //jeżeli stan wody jest niski (0) to wysyła alert o zalaniu
    digitalWrite(WATER_OUT_PIN, HIGH);
    int waterState = digitalRead(WATER_IN_PIN);
 
    char payload[256];
    snprintf(payload, sizeof(payload),
    "{\"sensorType\":\"water\",\"timestamp\":%d,\"alert\":%s}",
    now, (waterState == 0) ? "true" : "false");
    
    Serial.printf("[WATER] Payload: %s\r\n", payload);
    sendToIoTHub(payload);
}
