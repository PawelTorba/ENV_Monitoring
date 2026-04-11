#include "temp_hum.h"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>
#include "azure.h"

// THIS DHT SENSOR CODE CAN ONLY HANDLE SIMULATION MODE, REAL SENSOR READING CODE IS NOT IMPLEMENTED YET

// ===== SIMULATION =====
dht_reading_t generateFakeDHT() {
    dht_reading_t f;
    f.temperature = 15 + (rand() % 2500) / 100.0; // 15°C to 40°C
    f.humidity = 20 + (rand() % 7000) / 100.0; // 20% to 90% humidity
    return f;
}

void triggerAlarm_DHT(dht_reading_t data, int now) {
    //TO DO: SEND ALERT TO AZURE OR OTHER CLOUD SERVICE
    //TO DO: ADD LED ALERT
}

void handleDHTValues(dht_reading_t data, int now) {

// Create JSON payload structure for Azure IoT Hub
    char payload[256];
    snprintf(payload, sizeof(payload),
        "{\"sensorType\":\"dht\",\"temperature\":%.2f,\"humidity\":%.2f,\"timestamp\":%d, \"alert\":%s, alert-object\": {\"temperatureAlert\": %s, \"humidityAlert\": %s}}",
        data.temperature,
        data.humidity,
        now,
        (data.temperature > TEMP_THRESHOLD || data.humidity > HUM_THRESHOLD) ? "true" : "false",
        (data.temperature > TEMP_THRESHOLD) ? "true" : "false",
        (data.humidity > HUM_THRESHOLD) ? "true" : "false"
    );
    
    Serial.printf("[DHT] Payload: %s\r\n", payload);
    //TO DO: SEND payload TO AZURE IOT HUB
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

