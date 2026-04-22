/***********************************************************************************************************************
 * File Name    : i2c_sensor.c
 * Description  : I2C communication with MCP9808 temperature sensor
 **********************************************************************************************************************/
#include "common_utils.h"
#include "i2c_sensor.h"
static volatile bool callback_called = false;
/* MCP9808 Configuration Temperature Register b:xxxx0101 */
uint8_t reg_pointer = 0x05; //0x05
/* 2-byte buffer that contains I2C data */
uint8_t i2c_rx_buffer[2];
static int16_t mcp9808_to_celsius(void);
/*******************************************************************************************************************//**
 * @brief  Initialize the I2C master for sensor communication.
 *
 * Opens and initializes the I2C master driver for MCP9808 temperature sensor.
 * Must be called before any sensor read operations.
 **********************************************************************************************************************/
void init_sensor()
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_IIC_MASTER_Open (&g_i2c_master_ctrl, &g_i2c_master_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_IIC_MASTER_Open API failed ** \r\n");
        APP_ERR_TRAP(err);
    }
    return;
}

/*******************************************************************************************************************//**
 * @brief  Read temperature data from MCP9808 sensor.
 *
 * Performs I2C write to set register pointer, then reads temperature data.
 * This function blocks until I2C operations complete via callback.
 *
 * @retval  Temperature value in degrees Celsius
 **********************************************************************************************************************/
int16_t read_sensor_data()
{
    fsp_err_t err = FSP_SUCCESS;
    callback_called = false;
    err = R_IIC_MASTER_Write (&g_i2c_master_ctrl, &reg_pointer, 1, true);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_IIC_MASTER_Write API failed ** \r\n");
        APP_ERR_TRAP(err);
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
        APP_ERR_TRAP(err);
    }
    while (callback_called != true)
    {
        ;
    }
    callback_called = false;
    int16_t temperature = mcp9808_to_celsius ();
    return temperature;
}

/*******************************************************************************************************************//**
 * @brief  Convert MCP9808 raw data to Celsius temperature.
 *
 * Converts the 2-byte raw data from MCP9808 temperature register to
 * a signed integer temperature value in degrees Celsius.
 * Uses double buffering to avoid conflicts with I2C receive buffer.
 *
 * @retval  Temperature value in degrees Celsius (positive or negative)
 **********************************************************************************************************************/
static int16_t mcp9808_to_celsius()
{
    /*Use double buffering for safety*/
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

/*******************************************************************************************************************//**
 * @brief  Callback function for I2C master operations.
 *
 * Called by the I2C driver when TX or RX operation completes.
 * Sets a flag to indicate completion.
 *
 * @param[in]  p_args  Pointer to callback arguments containing the I2C event
 **********************************************************************************************************************/
void i2c_master_callback(i2c_master_callback_args_t *p_args)
{
    if (p_args->event == I2C_MASTER_EVENT_TX_COMPLETE || p_args->event == I2C_MASTER_EVENT_RX_COMPLETE)
    {
        callback_called = true;
    }
}
