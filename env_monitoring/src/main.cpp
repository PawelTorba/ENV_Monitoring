#include <Arduino.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// GAS PINOUT
#define GAS_DIGITAL_PIN 12
#define GAS_ANALOG_PIN 34   // GPIO34 = ADC1

// TEMP PINOUT
#define DHT_PIN 27

// FLOOD PINOUT
#define WATER_OUT_PIN 25
#define WATER_IN_PIN  26

// MOTION SENSOR
#define PIR_PIN 2

// THRESHOLDS
#define GAS_THRESHOLD 700
#define TEMP_THRESHOLD 30.0
#define HUM_THRESHOLD 70.0

#define ABSENCE_TIMEOUT_MS 15000

int lastMotionTime = 0;
bool occupied = false;
bool simulationMode = true;

// ===== STRUCT =====
typedef struct {
    float temperature;
    float humidity;
} dht_reading_t;

// ===== ALERTS =====
void triggerAlarm_Gas(int value) {
    Serial.printf("!!! ALARM GAZU !!! %d\n", value);
}

void triggerAlarm_DHT(dht_reading_t data) {
    Serial.printf("!!! ALARM DHT !!! Temp: %.2f Hum: %.2f\n",
                  data.temperature, data.humidity);
}

void triggerAlarm_Water() {
    Serial.println("!!! ALARM ZALANIA !!!");
}

void notifyMotionDetected() {
    Serial.println("🟢 RUCH WYKRYTY");
}

void notifyNoMotion() {
    Serial.println("🔴 BRAK RUCHU");
}

// ===== SIMULATION =====
int generateFakeGasValue() {
    return rand() % 1024;
}

dht_reading_t generateFakeDHT() {
    dht_reading_t f;
    f.temperature = 15 + (rand() % 2500) / 100.0;
    f.humidity = 20 + (rand() % 7000) / 100.0;
    return f;
}

int simulatePIR() {
    return (rand() % 10) < 2;
}

// ===== SETUP =====
void setup() {
    Serial.begin(115200);
    srand(time(NULL));

    pinMode(GAS_DIGITAL_PIN, INPUT);
    pinMode(PIR_PIN, INPUT);

    pinMode(WATER_OUT_PIN, OUTPUT);
    pinMode(WATER_IN_PIN, INPUT_PULLUP);

    pinMode(DHT_PIN, INPUT);
}

// ===== LOOP =====
void loop() {

    int now = millis();

    // ===== PIR =====
    int pir = simulationMode ? simulatePIR() : digitalRead(PIR_PIN);

    if (pir == 1) {
        lastMotionTime = now;

        if (!occupied) {
            occupied = true;
            notifyMotionDetected();
        }
    } else {
        if (occupied && (now - lastMotionTime > ABSENCE_TIMEOUT_MS)) {
            occupied = false;
            notifyNoMotion();
        }
    }

    // ===== GAS =====
    int analogValue;
    int digitalValue;

    if (simulationMode) {
        analogValue = generateFakeGasValue();
        digitalValue = analogValue > GAS_THRESHOLD;
    } else {
        analogValue = analogRead(GAS_ANALOG_PIN);
        digitalValue = digitalRead(GAS_DIGITAL_PIN);
    }

    Serial.printf("[GAS] %d | %d\n", analogValue, digitalValue);

    if (analogValue > GAS_THRESHOLD || digitalValue == 1) {
        triggerAlarm_Gas(analogValue);
    }

    // ===== DHT (SIMULATION ONLY) =====
    dht_reading_t dht;

    if (simulationMode) {
        dht = generateFakeDHT();
    } else {
        dht.temperature = 0;
        dht.humidity = 0;
    }

    Serial.printf("[DHT] T: %.2f H: %.2f\n", dht.temperature, dht.humidity);

    if (dht.temperature > TEMP_THRESHOLD || dht.humidity > HUM_THRESHOLD) {
        triggerAlarm_DHT(dht);
    }

    // ===== WATER =====
    digitalWrite(WATER_OUT_PIN, HIGH);
    int waterState = digitalRead(WATER_IN_PIN);

    Serial.printf("[WATER] %d\n", waterState);

    if (waterState == 0) {
        triggerAlarm_Water();
    }

    delay(2000);
}