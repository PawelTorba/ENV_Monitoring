#include <Arduino.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "gas.h"
#include "motion.h"
#include "temp_hum.h"
#include "water.h"

// Set to true to enable simulation mode, false to read actual sensor values
bool simulationMode = true; 

/////////////////////////////////////////////////////////////////////////////
////// SETUP -- PINOUT DEFINITIONS AND INITIALIZATIONS IN HEADER FILES //////
/////////////////////////////////////////////////////////////////////////////

void setup() {
    Serial.begin(115200);
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

    int now = millis();

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

    //OPÓŹNIENIE 2 SEKUNDY MIĘDZY KOLEJNYMI PĘTLAMI
    delay(2000);
}