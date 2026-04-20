/*
 * i2c_sensor.h
 *
 *  Created on: 20 Απρ 2026
 *      Author: a5163766
 */
#include "defenitions.h"
#include "hal_data.h"

#ifndef I2C_SENSOR_H_
#define I2C_SENSOR_H_
float mcp9808_raw_to_celsius(uint8_t *buf);
fsp_err_t init_sensor(void);
fsp_err_t read_sensor_data(void);
extern float temperature;
#endif /* I2C_SENSOR_H_ */
