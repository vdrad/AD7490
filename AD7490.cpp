/**
 * @file  AD7490.cpp
 * @brief Arduino library for AD7490 (12-bit, 16-channel ADC).
 * @author Victor Gomes
 */

#include "AD7490.h"

void AD7490::begin() {
    pinMode(CSPin, OUTPUT);
    digitalWrite(CSPin, HIGH);

    SPI.begin(
        SCLKPin,
        DOUTPin,
        DINPin,
        CSPin
    );

    reset();
}

uint16_t AD7490::read(uint8_t channel) {
    uint16_t command = generateCommand(channel);

    write(command);
    // We only receive the requested data on the next write, so we have to send a blank request.
    uint16_t response = write(0);
    // Response is composed of ADDRESS+DATA, so we remove the ADDRESS.
    response &= 0x0FFF;

    return response;
}

void AD7490::validate() {
    for (uint8_t channel = 0; channel < 16; channel++) {
        uint16_t reading = read(channel);
        Serial.print("CH");
        Serial.print(channel);
        Serial.print(": ");
        Serial.print(reading);
        Serial.print("|");
    }

    Serial.println("\n");
}

uint16_t AD7490::generateCommand(uint8_t address) {
    // Uses bitwise operators to assemble the required command to read data from AD7490.
    // For more information on that, read AD74901's datasheet.
    return ((
        (AD7490_CR_WRITE_VALUE  <<11)   |
        (AD7490_CR_SEQ_VALUE    <<10)   |
        ((uint16_t)address      <<6)    |
        (AD7490_CR_PM_VALUE     <<4)    |
        (AD7490_CR_SHADOW_VALUE <<3)    |
        (AD7490_CR_WEAK_VALUE   <<2)    |
        (AD7490_CR_RANGE_VALUE  <<1)    |
        (AD7490_CR_CODING_VALUE)
    )<<4);
}

uint16_t AD7490::write(uint16_t command) {
    digitalWrite(CSPin, LOW);

    SPI.beginTransaction(
        SPISettings(
            clockFrequency,
            SPI_BIT_ORDER,
            SPI_MODE
        )
    );
    uint16_t response = SPI.transfer16(command);
    SPI.endTransaction();

    digitalWrite(CSPin, HIGH);

    return response;
}

void AD7490::reset() {
    // For more information on that, see AD7490's datasheet on page 21.
    write(UINT16_MAX);
    delay(10);
    write(UINT16_MAX);
    delay(10);

    uint16_t command = generateCommand(0);
    write(command);
}

void AD7490::setSCLKPin(uint8_t pin) {
    SCLKPin = pin;
}

void AD7490::setDOUTPin(uint8_t pin) {
    DOUTPin = pin;
}

void AD7490::setDINPin(uint8_t pin) {
    DINPin = pin;
}

void AD7490::setCSPin(uint8_t pin) {
    CSPin = pin;
}

void AD7490::setPins(uint8_t sclk, uint8_t dout, uint8_t din, uint8_t cs) {
    SCLKPin = sclk;
    DOUTPin = dout;
    DINPin  = din;
    CSPin   = cs;
}

void AD7490::setClockFrequency(uint32_t frequency) {
    clockFrequency = frequency;
}

void AD7490::begin(uint8_t sclk, uint8_t dout, uint8_t din, uint8_t cs) {
    setAllPins(
        sclk,
        dout,
        din,
        cs
    );

    begin();
}

void AD7490::begin(uint8_t sclk, uint8_t dout, uint8_t din, uint8_t cs, uint32_t frequency) {
    setAllPins(
        sclk,
        dout,
        din,
        cs
    );

    setClockFrequency(frequency);
    
    begin();
}