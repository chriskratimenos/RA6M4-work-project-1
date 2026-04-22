/*
 * i2c_sensor.h
 *
 *  Created on: 20 Απρ 2026
 *      Author: a5163766
 */
#include "hal_data.h"

#ifndef I2C_SENSOR_H_
#define I2C_SENSOR_H_
void init_sensor(void);
static int16_t mcp9808_to_celsius();
int16_t read_sensor_data();
#endif /* I2C_SENSOR_H_ */
