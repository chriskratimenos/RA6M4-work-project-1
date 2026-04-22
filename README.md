# Temperature Monitoring System for RA6M4

## Overview

This project implements a temperature monitoring system using the Renesas RA6M4 microcontroller (EK-RA6M4 evaluation kit). The system reads temperature data from both an external I2C sensor (THERMO 8 CLICK) and the internal ADC temperature sensor, averages the values, and stores them in Virtual EEPROM (VEE) Flash for persistent storage .

## Features

- **Dual Temperature Sensing**: Reads from external I2C sensor and internal ADC temperature sensor. 
- **Periodic Reading**: Timer-based temperature sampling at every 1 second. 
- **LED Indication**: LED toggles on each temperature reading. 
- **UART Output**: Transmits temperature data to serial terminal. 
- **Persistent Storage**: Stores temperature data in Virtual EEPROM Flash. 
- **Button Controls**: User interaction via S1 and S2 buttons. 
- **Low Power Mode**: SW Standby Mode for reduced power consumption. 

## Hardware Requirements

## Hardware

| Component | Description |
|-----------|-------------|
| MCU Board | [EK-RA6M4](https://www.renesas.com/products/microcontrollers-microprocessors/ra-cortex-m-mcus/ek-ra6m4-evaluation-kit-ra6m4-mcu-group)  |
| Temperature Sensor | [THERMO 8 CLICK](https://www.mikroe.com/thermo-8-click) or Renesas US082-HS3001EVZ  |
| USB to TTL Adapter | For UART serial output |

### Temperature Reading

- Reads temperature via I2C 
- Timer triggers periodic readings every X ms 
- LED toggles on each reading 
- Prints temperature to Serial Terminal via UART 
- Reads internal ADC temperature sensor to compare die temperature with ambient temperature 

### Logging

- Writes to Data Flash, not Code Flash 
- S1 button interrupt stops measurement and prints last 10 temperatures 
- Stores values into Data Flash 
- Reads last measured values from Flash 
- S1 button re-pressed resumes periodic measurement every X ms 
- Uses VEEPROM driver from FSP 

### Low Power Mode

- S2 button stops temperature measurements 
- Configures RA6M4 into SW Standby Mode to reduce power consumption 
- S2 button wakes device and continues temperature reading 
- AGT timer provides additional wake event 

## About
This is a training exercise for my Renesas Intership . 
