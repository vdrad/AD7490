/**
 * @file  AD7490_read.cpp
 * @brief Reads all channels from AD7490.
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
    /* Alternatively, you could do:
    ADC.begin(
        SLCK_PIN,
        DOUT_PIN,
        DIN_PIN,
        CS_PIN,
        CLOCK_FREQUENCY
    ); */
    Serial.println("AD7490 successfully configured!");
}

void loop() {
    ADC.validate();
    delay(2000);
}