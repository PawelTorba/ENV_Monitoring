#include <Arduino.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "gas.h"
#include "motion.h"
#include "temp_hum.h"
#include "water.h"
#include <WiFi.h>

// WiFi credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Set to true to enable simulation mode, false to read actual sensor values
bool simulationMode = true; 

/////////////////////////////////////////////////////////////////////////////
////// SETUP -- PINOUT DEFINITIONS AND INITIALIZATIONS IN HEADER FILES //////
/////////////////////////////////////////////////////////////////////////////

void setup() {

    Serial.begin(115200);
    delay(1000);
    
     // Connect to WiFi
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println(" WiFi connected!");
    } else {
        Serial.println(" WiFi connection failed!");
    }


    //TIME FOR AZURE IOT HUB
    configTime(0, 0, "pool.ntp.org");

    Serial.print("Syncing time...");
    while (time(NULL) < 100000) {
    delay(500);
    Serial.print(".");
    }
    Serial.println(" done");

    
    srand(time(NULL));

    pinMode(GAS_DIGITAL_PIN, INPUT);
    pinMode(PIR_PIN, INPUT);

    pinMode(WATER_OUT_PIN, OUTPUT);
    pinMode(WATER_IN_PIN, INPUT_PULLUP);

    pinMode(DHT_PIN, INPUT);
}

//////////////////////////////////////////////////////////
//////   LOOP / MAIN  -- WYKONUJE SIĘ CO "DELAY()"  //////
//////////////////////////////////////////////////////////
void loop() {

    int now = time(NULL);

    // ===== GAS =====
    handleGasSensor(simulationMode, now);
    delay(100);

    // ===== PIR =====
    handleMotionSensor(simulationMode, now);    
    delay(100);

    // ===== DHT =====
    handleDHTSensor(simulationMode, now);
    delay(100);

    // ===== WATER =====
    handleWaterSensor(simulationMode, now);
    delay(100);

    Serial.printf("---------------------------------------------\r\n");

    //OPÓŹNIENIE 10 SEKUND MIĘDZY KOLEJNYMI PĘTLAMI
    delay(59600);
}