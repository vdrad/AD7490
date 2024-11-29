/**
 * @file  AD7490.h
 * @brief Arduino library for AD7490 (12-bit, 16-channel ADC).
 * @author Victor Gomes
 */

#ifndef __AD7490_H__
#define __AD7490_H__

#include "Arduino.h"
#include "SPI.h"

/* MACROS */
// SPI 
#define DEFAULT_CLOCK_FREQUENCY 1e7         // 10 MHz
#define SPI_BIT_ORDER           MSBFIRST
#define SPI_MODE                SPI_MODE0

// DEFAULT PINS
// Chosen based on the test application.
#define DEFAULT_SCLK_PIN    41
#define DEFAULT_DOUT_PIN    40
#define DEFAULT_DIN_PIN     42
#define DEFAULT_CS_PIN      39

// AD7490 CONTROL REGISTER (CR)
#define DEFAULT_AD7490_CR_WRITE_VALUE  1
#define DEFAULT_AD7490_CR_SEQ_VALUE    0
#define DEFAULT_AD7490_CR_PM_VALUE     3
#define DEFAULT_AD7490_CR_SHADOW_VALUE 0
#define DEFAULT_AD7490_CR_WEAK_VALUE   1
#define DEFAULT_AD7490_CR_RANGE_VALUE  1
#define DEFAULT_AD7490_CR_CODING_VALUE 1

/* AD7490 CLASS*/
class AD7490{
    public:
        // Functions

        /** 
         * @brief begins SPI communication for AD7490.
         * @warning Make sure to call set pin functions before calling begin().
         * @warning Make sure to call setClock before calling begin().
        */
        void begin();
        /** 
         * @brief begins SPI communication for AD7490.
         * @param sclk, din, dout, cs
        */
        void begin(uint8_t sclk, uint8_t dout, uint8_t din, uint8_t cs);
        /** 
         * @brief begins SPI communication for AD7490.
         * @param sclk, din, dout, cs, frequency
        */
        void begin(uint8_t sclk, uint8_t dout, uint8_t din, uint8_t cs, uint32_t frequency);

        /** 
         * @brief reads a channel from AD7490.
         * @param channel
         * @return adc reading
        */
        uint16_t read(uint8_t channel);

        /** 
         * @brief prints AD7490 readings for each channel.
         * @warning you need to call Serial.begin() first.
        */
        void validate();

        /** 
         * @brief sets Clock (SCLK) pin for SPI communication.
         * @param pin
         * @warning this should be called before begin().
        */
        void setSCLKPin(uint8_t pin);

        /** 
         * @brief sets Data In (DIN) pin, i.e data sent TO the AD7490, for SPI communication.
         * @param pin
         * @warning this should be called before begin().
        */
        void setDINPin(uint8_t pin);

        /** 
         * @brief sets Data In (DOUT) pin, i.e data sent FROM the AD7490, for SPI communication.
         * @param pin
         * @warning this should be called before begin().
        */
        void setDOUTPin(uint8_t pin);

        /** 
         * @brief sets Chip Select (CS) pin for SPI communication.
         * @param pin
         * @warning this should be called before begin().
        */
        void setCSPin(uint8_t pin);

        /** 
         * @brief sets all pins for SPI communication.
         * @param sclk, din, dout, cs
         * @warning this should be called before begin().
        */
        void setPins(uint8_t sclk, uint8_t din, uint8_t dout, uint8_t cs);

        /** 
         * @brief sets SPI clock frequency.
         * @param frequency
         * @warning this should be called before begin().
        */
        void setClockFrequency(uint32_t frequency);

        /** 
         * @brief sets the Sequencer (SEQ) bit of the Control Register (CR).
         * @param value
        */
        void setSequencer(uint8_t value);

        /** 
         * @brief sets the Power Mode (PM) bit of the Control Register (CR).
         * @param value
        */
        void setPowerMode(uint8_t value);

        /** 
         * @brief sets the Power Mode (PM) of AD7490.
         * @param value
        */
        void setShadow(uint8_t value);

        /** 
         * @brief sets the Weak bit of the Control Register (CR).
         * @param value
        */
        void setWeak(uint8_t value);

        /** 
         * @brief sets the Range of AD7490.
         * @param value
        */
        void setRange(uint8_t value);

        /** 
         * @brief sets the Coding bit of the Control Register (CR).
         * @param value
        */
        void setCoding(uint8_t value);

        /** 
         * @brief sets the Control Register (CR) bits.
         * @param seq, pm, shadow, weak, range, coding
        */
        void setCR(uint8_t seq, uint8_t pm, uint8_t shadow, uint8_t weak, uint8_t range, uint8_t coding);

    private:
        // Variables
        uint8_t SCLKPin         = DEFAULT_SCLK_PIN;
        uint8_t DOUTPin         = DEFAULT_DOUT_PIN;
        uint8_t DINPin          = DEFAULT_DIN_PIN;
        uint8_t CSPin           = DEFAULT_CS_PIN;
        uint32_t clockFrequency = DEFAULT_CLOCK_FREQUENCY;
        uint8_t  CRWriteValue   = DEFAULT_AD7490_CR_WRITE_VALUE;
        uint8_t  CRSEQValue     = DEFAULT_AD7490_CR_SEQ_VALUE;
        uint8_t  CRPMValue      = DEFAULT_AD7490_CR_PM_VALUE;
        uint8_t  CRShadowValue  = DEFAULT_AD7490_CR_SHADOW_VALUE;
        uint8_t  CRWeakValue    = DEFAULT_AD7490_CR_WEAK_VALUE;
        uint8_t  CRRangeValue   = DEFAULT_AD7490_CR_RANGE_VALUE;
        uint8_t  CRCodingValue  = DEFAULT_AD7490_CR_CODING_VALUE;

        // Functions
        /** 
         * @brief generates the required command to perform a channel reading.
         * @return command
        */
        uint16_t generateCommand(uint8_t address);

        /** 
         * @brief writes a command to AD7490 registers.
         * @param command
        */
        uint16_t write(uint16_t command);
        
        /** 
         * @brief reset AD7490 according to its datasheet.
        */
        void reset();
};
#endif