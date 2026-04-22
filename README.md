# Temperature Monitoring System for RA6M4

## Overview

This project implements a temperature monitoring system using the Renesas RA6M4 microcontroller. 
The system reads temperature data from both an external I2C sensor (MCP9808) and the internal 
ADC temperature sensor, averages the values, and stores them in Virtual EEPROM (VEE) Flash 
for persistent storage.

## Features

- **Dual Temperature Sensing**: Reads from MCP9808 I2C sensor and internal ADC temperature sensor
- **Data Averaging**: Combines both sensor readings for improved accuracy
- **Persistent Storage**: Stores temperature data in Virtual EEPROM Flash
- **UART Output**: Transmits temperature data over serial communication
- **Low Power Mode**: Supports sleep mode for power conservation
- **Button Controls**: User interaction via S1 and S2 buttons

## Hardware Requirements

| Component | Description |
|-----------|-------------|
| MCU | Renesas RA6M4 |
| Temperature Sensor | MCP9808 (I2C) |
| Communication | UART (Serial) |
| User Interface | S1 Button, S2 Button, LED1, LED2, LED3 |

## Pin Configuration

| Function | Pin | Description |
|----------|-----|-------------|
| LED1 | - | Temperature reading indicator |
| LED2 | - | Display mode indicator |
| LED3 | - | Low power mode indicator |
| S1 Button | - | Toggle read/display mode |
| S2 Button | - | Enter low power mode |
| I2C SDA | - | MCP9808 data line |
| I2C SCL | - | MCP9808 clock line |
| UART TX | - | Serial transmit |
| UART RX | - | Serial receive |

## Software Architecture

### Module Structure
