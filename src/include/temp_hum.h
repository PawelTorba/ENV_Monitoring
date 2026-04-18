#ifndef TEMP_HUM_H
#define TEMP_HUM_H

#define DHT_PIN 27

#define TEMP_THRESHOLD 30.0
#define HUM_THRESHOLD 70.0

typedef struct {
    float temperature;
    float humidity;
} dht_reading_t;

void triggerAlarm_DHT(dht_reading_t data, int now);
void handleDHTSensor(bool simulationMode, int now);

dht_reading_t generateFakeDHT(void);

#endif