# Temperature Monitoring System for RA6M4

## Overview

This project implements a temperature monitoring system using the Renesas RA6M4 microcontroller (EK-RA6M4 evaluation kit). The system reads temperature data from both an external I2C sensor (MCP9808/THERMO 8 CLICK) and the internal ADC temperature sensor, averages the values, and stores them in Virtual EEPROM (VEE) Flash for persistent storage [1].

## Features

- **Dual Temperature Sensing**: Reads from external I2C sensor and internal ADC temperature sensor 
- **Periodic Reading**: Timer-based temperature sampling at configurable intervals 
- **LED Indication**: LED toggles on each temperature reading 
- **UART Output**: Transmits temperature data to serial terminal 
- **Persistent Storage**: Stores temperature data in Virtual EEPROM Flash 
- **Button Controls**: User interaction via S1 and S2 buttons 
- **Low Power Mode**: SW Standby Mode for reduced power consumption 

## Hardware Requirements

| Component | Description |
|-----------|-------------|
| MCU Board | Renesas EK-RA6M4 |
| Temperature Sensor | THERMO 8 CLICK |
| Communication | UART (Serial Terminal) |
| User Interface | S1 Button, S2 Button, LEDs |

