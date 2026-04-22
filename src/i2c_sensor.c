#include "common_utils.h"
#include "i2c_sensor.h"
static volatile bool callback_called = false;
/* MCP9808 Configuration Temperature Register b:xxxx0101*/
uint8_t reg_pointer = 0x05; //0x05
/*2 byte Buffer that contains i2c data*/
uint8_t i2c_rx_buffer[2];

void init_sensor()
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_IIC_MASTER_Open (&g_i2c_master_ctrl, &g_i2c_master_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_IIC_MASTER_Open API failed ** \r\n");
    }
    return;
}

int16_t read_sensor_data()
{
    fsp_err_t err = FSP_SUCCESS;
    callback_called = false;
    err = R_IIC_MASTER_Write (&g_i2c_master_ctrl, &reg_pointer, 1, true);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_IIC_MASTER_Write API failed ** \r\n");
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
    }
    while (callback_called != true)
    {
        ;
    }
    callback_called = false;
    int16_t temperature = mcp9808_to_celsius ();
    return temperature;
}

/* Callback function */
void i2c_master_callback(i2c_master_callback_args_t *p_args)
{
    if (p_args->event == I2C_MASTER_EVENT_TX_COMPLETE || p_args->event == I2C_MASTER_EVENT_RX_COMPLETE)
    {
        callback_called = true;
    }
}

static int16_t mcp9808_to_celsius()
{
    //Use double buffering to avoid conflicts
    uint8_t rx_buffer[2];
    memcpy(rx_buffer,i2c_rx_buffer,sizeof(rx_buffer));

    int16_t temperature;
    /*Clear flag bits*/
    rx_buffer[0] = rx_buffer[0] & 0x1F; // Masks last 3 bits

    if ((rx_buffer[0] & 0x10) == 0x10)    // Temperature < 0
    {
        /*Clear SIGN (with the flag)*/
        rx_buffer[0] = rx_buffer[0] & 0x0F;
        temperature = 256 - (rx_buffer[0] * 16 + rx_buffer[1] / 16);
    }
    else    //Temperature>0
    {
        temperature = (rx_buffer[0] * 16 + rx_buffer[1] / 16);
    }
    return temperature;
}

