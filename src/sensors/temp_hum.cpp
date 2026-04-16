#include "temp_hum.h"
#include <Arduino.h>
#include <stdlib.h> 
#include <time.h>
#include "azure.h"

// THIS DHT SENSOR CODE CAN ONLY HANDLE SIMULATION MODE

// ===== SIMULATION =====
// stara symulacja DHT
//dht_reading_t generateFakeDHT() {
//     dht_reading_t f;
//     f.temperature = 15 + (rand() % 2500) / 100.0; // 15°C to 40°C
//     f.humidity = 20 + (rand() % 7000) / 100.0; // 20% to 90% humidity
//     return f;
// }

dht_reading_t generateFakeDHT() {
    // bardziej realne wartości temperatury i wilgotności z lekkimi losowymi zmianami, ale bez nagłych skoków (chyba że raz na jakiś czas)
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

    if ((rand() % 1000) == 0) { // 0.1% szansy
        temp += 5 + (rand() % 5); // skok do 30+
    }

    dht_reading_t f;
    f.temperature = temp;
    f.humidity = hum;
    return f;
}

void triggerAlarm_DHT(dht_reading_t data, int now) {
    //TO DO: ADD LED ALERT
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

    // char payload[256];
    // snprintf(payload, sizeof(payload),
    //     "{\"sensorType\":\"dht\",\"temperature\":%.2f,\"humidity\":%.2f,\"timestamp\":%d, \"alert\":%s, \"alertTemp\": %s, \"alertHum\": %s, \"thresholds\": {\"temperatureThreshold\": %.2f, \"humidityThreshold\": %.2f}}",
    //     data.temperature,
    //     data.humidity,
    //     now,
    //     (data.temperature > TEMP_THRESHOLD || data.humidity > HUM_THRESHOLD) ? "true" : "true",
    //     (data.temperature > TEMP_THRESHOLD) ? "true" : "true",
    //     (data.humidity > HUM_THRESHOLD) ? "true" : "true",
    //     TEMP_THRESHOLD,
    //     HUM_THRESHOLD
    // );
    
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

