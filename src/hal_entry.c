#include "hal_data.h"
#include "common_utils.h"
#include "vee_flash.h"
#include "defenitions.h"
#include "s1_button.h"
#include "s2_button.h"


void flash_main(void);
void start_peripherals();
uint8_t temperature[NUM_TEMPERATURE_RECORDINGS];
volatile bool low_power_mode=false;

void flash_main(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = vee_flash_init ();
    APP_ERR_TRAP(err);
    vee_format_operation ();
    APP_ERR_TRAP(err);
    for (uint32_t i = 0; i < NUM_TEMPERATURE_RECORDINGS; i++)
    {
        temperature[i] = 0xAA;
    }
    err = vee_write_operation (TEMPERATURE_ID, temperature, NUM_TEMPERATURE_RECORDINGS);
    APP_ERR_TRAP(err);

    for (uint32_t i = 0; i < NUM_TEMPERATURE_RECORDINGS; i++)
    {
        temperature[i] = 0xBB;
    }
    err = vee_write_operation (TEMPERATURE_ID, temperature, NUM_TEMPERATURE_RECORDINGS);
    APP_ERR_TRAP(err);

    for (uint32_t i = 0; i < NUM_TEMPERATURE_RECORDINGS; i++)
    {
        temperature[i] = 0xCC;
    }
    err = vee_write_operation (TEMPERATURE_ID, temperature, NUM_TEMPERATURE_RECORDINGS);
    APP_ERR_TRAP(err);
}

void start_peripherals()
{
    flash_main ();
    fsp_err_t err = FSP_SUCCESS;
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
    return;
}

void hal_entry(void)
{
    APP_PRINT("\nStarting");
    start_peripherals ();
    /*Enable Low Power Mode*/
    fsp_err_t err = FSP_SUCCESS;
    err = R_LPM_Open (&g_lpm0_ctrl, &g_lpm0_cfg);
    APP_ERR_TRAP(err);

    while (1)
    {
        if (low_power_mode == true)
        {
            err = R_LPM_LowPowerModeEnter (&g_lpm0_ctrl);
            if (FSP_SUCCESS != err)
            {
                /* ICU Enable failure message */
                APP_ERR_PRINT("\r\n**R_ICU_ExternalIrqEnable API FAILED**\r\n");
            }
            low_power_mode=false;
        }
    }
}

void irq_s2_cb(external_irq_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    low_power_mode = true;
    return;
}

