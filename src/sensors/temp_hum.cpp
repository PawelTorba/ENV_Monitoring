#include "temp_hum.h"
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>

// THIS DHT SENSOR CODE CAN ONLY HANDLE SIMULATION MODE, REAL SENSOR READING CODE IS NOT IMPLEMENTED YET

// ===== SIMULATION =====
dht_reading_t generateFakeDHT() {
    dht_reading_t f;
    f.temperature = 15 + (rand() % 2500) / 100.0; // 15°C to 40°C
    f.humidity = 20 + (rand() % 7000) / 100.0; // 20% to 90% humidity
    return f;
}

void triggerAlarm_DHT(dht_reading_t data) {
    Serial.printf("[DHT SENSOR] ALARM DHT - Temp: %.2f Hum: %.2f\n",
                  data.temperature, data.humidity);

    //TO DO: SEND ALERT TO AZURE OR OTHER CLOUD SERVICE
    //TO DO: ADD LED ALERT
}

void handleDHTValues(dht_reading_t data) {
    Serial.printf("[DHT] T: %.2f H: %.2f\n", data.temperature, data.humidity);

    //TO DO: SEND DATA TO AZURE OR OTHER CLOUD SERVICE
}

void handleDHTSensor(bool simulationMode){
    dht_reading_t dht;

    if (simulationMode) {
        dht = generateFakeDHT();
    } else {
        dht.temperature = 0;
        dht.humidity = 0;
    }

    handleDHTValues(dht);

    //HANDLE POTENTIAL ALERTS
    if (dht.temperature > TEMP_THRESHOLD || dht.humidity > HUM_THRESHOLD) {
        triggerAlarm_DHT(dht);
    }
}
