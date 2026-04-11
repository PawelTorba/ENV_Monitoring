#ifndef TEMP_HUM_H
#define TEMP_HUM_H

// TEMP PINOUT
#define DHT_PIN 27

// THRESHOLDS
#define TEMP_THRESHOLD 30.0 // 30°C
#define HUM_THRESHOLD 70.0 // 70% humidity

// DHT DATA STRUCTURE
typedef struct {
    float temperature;
    float humidity;
} dht_reading_t;

void triggerAlarm_DHT(dht_reading_t data, int now);
void handleDHTSensor(bool simulationMode, int now);

// SIMULATION
dht_reading_t generateFakeDHT(void);

#endif // TEMP_HUM_H