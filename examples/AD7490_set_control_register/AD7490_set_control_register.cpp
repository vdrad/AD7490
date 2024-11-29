/**
 * @file  AD7490_read.cpp
 * @brief Sets the Control Register (CR) of AD7490.
 * @author Victor Gomes
 */

#include "Arduino.h"
#include "AD7490.h"

#define SLCK_PIN        41
#define DOUT_PIN        40
#define DIN_PIN         42
#define CS_PIN          39
#define CLOCK_FREQUENCY 1e7

AD7490 ADC;

void setup() {
    Serial.begin(115200);

    Serial.println("Initializing AD7490...");
    ADC.setPins(SLCK_PIN, DOUT_PIN, DIN_PIN, CS_PIN);
    ADC.setClockFrequency(CLOCK_FREQUENCY);
    ADC.begin();
    Serial.println("AD7490 successfully configured!");

    Serial.println("Changing CR values...");
    ADC.setSequentialMode(0);
    ADC.setPowerMode(3);
    ADC.setShadow(0);
    ADC.setWeak(1);
    ADC.setRange(1);
    ADC.setCoding(1);
    /*Alternatively, you can do:
    ADC.setCR(0, 3, 0, 1, 1, 1,);
    */
    Serial.println("CR values changed successfully!");
}

void loop() {
    ADC.validate();
    delay(2000);
}