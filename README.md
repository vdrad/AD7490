[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![GitHub release](https://img.shields.io/github/release/vdrad/AD7490.svg?maxAge=3600)](https://github.com/vdrad/AD7490/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/vdrad/library/AD7490.svg)](https://registry.platformio.org/libraries/vdrad/AD7490)
# AD7490

Arduino library for AD7490 (12-bit, 16-channel ADC with SPI communication).

## Table of Contents

- [Description](#-description)
- [Hardware Connection](#️-hardware-connection)
- [How to Use](#-how-to-use)
    - [Including](#-including)
    - [Initializing](#-initializing)
    - [Testing](#-testing)
    - [Regular Operation](#-regular-operation)
- [Limitations](#-limitations)
    - [Clock Frequency](#-clock-frequency)
    - [Development](#-development)
- [Additional Information](#-additional-information)
- [Feedback and Contributions](#-feedback-and-contributions)
- [Contact](#️-contact)

## Description

**AD7490** is a library for the AD7490, a 12-bit, 16-channel Analog to Digital Converter (ADC) from [Analog Devices](https://www.analog.com/en/index.html) that works with SPI communication.

You can find more information on the device reading its [datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ad7490.pdf).

## Hardware Connection

The AD7490 requires all base pins from SPI:

- SCLK (Serial Clock)
- DOUT (Data Out from the AD7490, i.e, MISO)
- DIN (Data In to the AD7490, i.e, MOSI)
- CS (Chip Select, i.e, SS)

> [!IMPORTANT]  
> Even if you're only going to use one device, a CS pin must be connected. AD7490 requires a start-up routine (see datasheet's page 21) that involves manipulating the CS pin. 

## How to Use

### Including

```cpp
#include "AD7490.h"
```

### Initializig

You can initialize a sensor instance in three different ways:

```cpp
AD7490 ADC;

void setup() {
    ADC.setPins(41, 40, 42, 39); // SCLK, DOUT, DIN, CS
    ADC.setClockFrequency(1e7);  // 10 MHz
    ADC.begin();
}
```

```cpp
AD7490 ADC;

void setup() {
    ADC.setClockFrequency(1e7);  // 10 MHz
    ADC.begin(41, 40, 42, 39);
}
```

```cpp
AD7490 ADC;

void setup() {
    ADC.begin(41, 40, 42, 39, 1e7);
}
```

You can change (if needed) the Control Register (CR) parameters in two different ways:
```cpp
void setup() {
    ADC.setSequencer(0);
    ADC.setPowerMode(3);
    ADC.setShadow(0);
    ADC.setWeak(1);
    ADC.setRange(1);
    ADC.setCoding(1);
}
```

```cpp
void setup() {
    ADC.setCR(0, 3, 0, 1, 1, 1,);
}
```

See 📁examples fore more information.

### Testing
```cpp
void loop() {
    ADC.validate();
    delay(2000);
}
```

### Regular Operation
```cpp
void loop() {
    uint16_t reading = ADC.read(0); // Reads channel 0
}
```

## Limitations

### Clock Frequency

The maximum frequency tested was 10 MHz. This doesn't mean it's the maximum frequency that the device can operate.

### Development

This code was tested on an ESP32-S3-WROOM-N16R0. While it likely contains no ESP-specific code, conflicts may still arise. If you encounter any issues, please let me know.


Although it will likely work, I have not tested the library with multiple devices connected, whether multiple AD7490 units or other SPI devices on the same bus.

## Additional Information
To retrieve a reading from AD7490, you have to manipulate its internal Control Register (CR). Data is loaded from DIN pin on the falling edge of SCLK. The control register follows the given arrangement:

| **MSB** 	|        	|       	|       	|       	|       	|       	|       	|        	|           	|       	| **LSB** 	|
|---------	|--------	|-------	|-------	|-------	|-------	|-------	|-------	|--------	|-----------	|-------	|---------	|
|  **11** 	| **10** 	| **9** 	| **8** 	| **7** 	| **6** 	| **5** 	| **4** 	|  **3** 	|   **2**   	| **1** 	|  **0**  	|
|  WRITE  	|   SEQ  	|  ADD3 	|  ADD2 	|  ADD1 	|  ADD0 	|  PM1  	|  PM0  	| SHADOW 	| WEAK/TRI~ 	| RANGE 	|  CODING 	|

Therefore, when we perform a ```read(channel)```, the library internally assembles the necessary CR command. For more information on that, please read page 12 of AD7490's datasheet.

## Feedback and Contributions

For feedbacks, suggestions, collaboration opportunities, or any other topic, please feel free to reach out:

- Email:    victor.drad.g@gmail.com
- LinkedIn: [Victor Gomes](https://www.linkedin.com/in/victor-g-582b5911b/)
