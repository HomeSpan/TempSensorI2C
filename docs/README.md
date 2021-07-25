# TempSensorI2C - A HomeSpan Project

TempSensorI2C is a working example of how to use the I2C protocol to capture temperature readings from an Analog Device ADT7410 high-resolution temperature sensor and stream them to HomeKit.  Built using the [HomeSpan](https://github.com/HomeSpan/HomeSpan) HomeKit Library, TempSensorI2C is designed to run on an ESP32 device as an Arduino sketch.  

Hardware used for this project:

* An ESP32 board, such as the [Adafruit HUZZAH32 – ESP32 Feather Board](https://www.adafruit.com/product/3405)
* An Analog Device ADT7410 Temperature Sensor, such as the [Adafruit ADT7410 Breakout Board](https://www.adafruit.com/product/4089)

## Overview

This simple HomeSpan sketch illustrates how the standard Arduino I2C library `Wire.h` can be used to capture temperature readings from an ADT7410 temperature sensor and stream them to HomeKit.   The sketch:
* implements a single HomeKit *Accessory* containing a HomeKit *TemperatureSensor Service*;
* captures samples from the ADT7410 every 5 seconds;
* sends updates to HomeKit only if the temperature has changed by more than 0.5 Celsius; and
* is easily modified to accomodate up to 4 ADT7410 sensors, each with their own unique I2C address.

## Connections

The connections below provide for I2C communicaiton between the ESP32 and the ADT7410 using the 7410's default address of 0x48:

|ADT7410|ESP32|
|-------|-----|
|VIN|3V|
|GND|GND|
|SDA|SDA|
|SCL|SCL|
|A0|unused|
|A1|unused|
|INT|unused|
|CT|unused|

---

### Feedback or Questions?

Please consider adding to the [Discussion Board](https://github.com/HomeSpan/HomeSpan/discussions), or email me directly at [homespan@icloud.com](mailto:homespan@icloud.com).




