#include "temp_hum.h"
#include <Arduino.h>
#include <stdlib.h> 
#include <time.h>
#include "azure.h"

dht_reading_t generateFakeDHT() {
    static float temp = 22.0;     
    static float hum = 45.0;

    float tempChange = ((rand() % 100) / 100.0 - 0.5) * 0.2; // ±0.1°C
    float humChange  = ((rand() % 100) / 100.0 - 0.5) * 0.5; // ±0.25%

    temp += tempChange;
    hum += humChange;

    if (temp < 20) temp = 20;
    if (temp > 26) temp = 26;

    if (hum < 30) hum = 30;
    if (hum > 60) hum = 60;

    if ((rand() % 10) == 0) { 
        temp += 5 + (rand() % 5); 
    }

    dht_reading_t f;
    f.temperature = temp;
    f.humidity = hum;
    return f;
}

void triggerAlarm_DHT(dht_reading_t data, int now) {
}

void handleDHTValues(dht_reading_t data, int now) {

    char payload[256];
    snprintf(payload, sizeof(payload),
        "{\"sensorType\":\"dht\",\"temperature\":%.2f,\"humidity\":%.2f,\"timestamp\":%d, \"alert\":%s, \"alertTemp\": %s, \"alertHum\": %s, \"temperatureThreshold\": %.2f, \"humidityThreshold\": %.2f}",
        data.temperature,
        data.humidity,
        now,
        (data.temperature > TEMP_THRESHOLD || data.humidity > HUM_THRESHOLD) ? "true" : "false",
        (data.temperature > TEMP_THRESHOLD) ? "true" : "false",
        (data.humidity > HUM_THRESHOLD) ? "true" : "false",
        TEMP_THRESHOLD,
        HUM_THRESHOLD
    );

    Serial.printf("[DHT] Payload: %s\r\n", payload);
    sendToIoTHub(payload);
}

void handleDHTSensor(bool simulationMode, int now){
    dht_reading_t dht;

    if (simulationMode) {
        dht = generateFakeDHT();
    } else {
        dht.temperature = 0;
        dht.humidity = 0;
    }

    handleDHTValues(dht, now);
    }

