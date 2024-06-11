/*
Copyright (c) 2024 Engr Din Muhammad
www.projexels.com

*/

#include <PZEM004Tv30.h>

#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17
#define PZEM_SERIAL Serial2

// Initialize three PZEM modules with addresses 0x01, 0x02, and 0x03
PZEM004Tv30 pzem1(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN, 0x01);
PZEM004Tv30 pzem2(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN, 0x02);
PZEM004Tv30 pzem3(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN, 0x03);

void setup() {
    // Debugging Serial port
    Serial.begin(115200);

    // Uncomment in order to reset the internal energy counter
    // pzem1.resetEnergy();
    // pzem2.resetEnergy();
    // pzem3.resetEnergy();
}

void readPZEMData(PZEM004Tv30& pzem, const char* label) {
    // Print the custom address of the PZEM
    Serial.print(label);
    Serial.print(" Custom Address: ");
    Serial.println(pzem.readAddress(), HEX);

    // Read the data from the sensor
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    // Check if the data is valid
    if(isnan(voltage)){
        Serial.println("Error reading voltage");
    } else if (isnan(current)) {
        Serial.println("Error reading current");
    } else if (isnan(power)) {
        Serial.println("Error reading power");
    } else if (isnan(energy)) {
        Serial.println("Error reading energy");
    } else if (isnan(frequency)) {
        Serial.println("Error reading frequency");
    } else if (isnan(pf)) {
        Serial.println("Error reading power factor");
    } else {
        // Print the values to the Serial console
        Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
        Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
        Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
        Serial.print("Energy: ");       Serial.print(energy, 3);    Serial.println("kWh");
        Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
        Serial.print("PF: ");           Serial.println(pf);
    }

    Serial.println();
}

void loop() {
    readPZEMData(pzem1, "PZEM 01");
    readPZEMData(pzem2, "PZEM 02");
    readPZEMData(pzem3, "PZEM 03");

    delay(2000);
}
