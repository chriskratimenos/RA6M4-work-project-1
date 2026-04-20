#include "common_utils.h"
#include "defenitions.h"
#include "i2c_sensor.h"
static volatile bool callback_called = false;
/* MCP9808 Configuration Temperature Register b:xxxx0101*/
uint8_t reg_pointer = 0x05; //0x05
/*2 byte Buffer that contains temperature data*/
uint8_t i2c_rx_buffer[2];
 float temperature=0;
fsp_err_t init_sensor()
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_IIC_MASTER_Open (&g_i2c_master_ctrl, &g_i2c_master_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_IIC_MASTER_Open API failed ** \r\n");
    }
    return err;
}

fsp_err_t read_sensor_data()
{
    fsp_err_t err = FSP_SUCCESS;
    callback_called = false;

    err = R_IIC_MASTER_Write (&g_i2c_master_ctrl, &reg_pointer, 1, false);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_IIC_MASTER_Write API failed ** \r\n");
        return err;
    }
    while (callback_called != true)
    {
        ;
    }
    callback_called = false;

    err = R_IIC_MASTER_Read (&g_i2c_master_ctrl, &i2c_rx_buffer[0], 2, false);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_IIC_MASTER_Read API failed ** \r\n");
        return err;
    }
    while (callback_called != true)
    {
        ;
    }
    callback_called = false;
    temperature=mcp9808_raw_to_celsius(i2c_rx_buffer);
    return err;
}

/* Callback function */
void i2c_master_callback(i2c_master_callback_args_t *p_args)
{
    if (p_args->event == I2C_MASTER_EVENT_TX_COMPLETE || p_args->event == I2C_MASTER_EVENT_RX_COMPLETE)
    {
        callback_called = true;
    }
    if (p_args->event == I2C_MASTER_EVENT_TX_COMPLETE || p_args->event == I2C_MASTER_EVENT_RX_COMPLETE)
    {
        callback_called = true;
    }
}


float mcp9808_raw_to_celsius(uint8_t *buf)
{
    int16_t raw;
    /* Combine bytes */
    raw = (int16_t)((buf[0] << 8) | buf[1]);

    /* Clear alert bits (bits 15..13) except sign */
    raw &= 0x1FFF;

    /* Sign extend if negative */
    if (raw & 0x1000)
    {
        raw |= 0xE000;
    }

    /* Convert to Celsius */
    return raw * 0.0625f;
}

