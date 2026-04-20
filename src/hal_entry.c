#include "hal_data.h"
#include "common_utils.h"
#include "vee_flash.h"
#include "defenitions.h"
#include "s1_button.h"
#include "s2_button.h"
#include "i2c_sensor.h"
void start_peripherals();
uint8_t temperatures[NUM_TEMPERATURE_RECORDINGS];

void start_peripherals()
{
    fsp_err_t err = FSP_SUCCESS;
    /*Initialize the VEE FLASH*/
    err = vee_flash_init ();
    APP_ERR_TRAP(err);
    /*Format the VEE FLASH*/
    err = vee_format_operation ();
    APP_ERR_TRAP(err);
    /* Initialize External IRQ driver*/
    err = icu_s1_open ();
    APP_ERR_TRAP(err);
    /* Enable External IRQ driver*/
    err = icu_s1_enable ();
    APP_ERR_TRAP(err);
    /* Initialize External IRQ driver*/
    err = icu_s2_open ();
    APP_ERR_TRAP(err);
    /* Enable External IRQ driver*/
    err = icu_s2_enable ();
    APP_ERR_TRAP(err);

    /* Enable Temperature Sensor*/
    err = init_sensor ();
    APP_ERR_TRAP(err);

    return;
}

void hal_entry(void)
{
    fsp_err_t err = FSP_SUCCESS;
    APP_PRINT("\nStarting");
    start_peripherals ();
    /*Enable Low Power Mode*/
    err = R_LPM_Open (&g_lpm0_ctrl, &g_lpm0_cfg);
    APP_ERR_TRAP(err);
    while (1)
    {
        err = read_sensor_data ();
        APP_ERR_TRAP(err);
        if (low_power_mode == true)
        {
            err = R_LPM_LowPowerModeEnter (&g_lpm0_ctrl);
            if (FSP_SUCCESS != err)
            {
                /* ICU Enable failure message */
                APP_ERR_PRINT("\r\n**R_ICU_ExternalIrqEnable API FAILED**\r\n");
            }
            low_power_mode = false;
        }
    }
}

