#include "common_utils.h"
#include "vee_flash.h"  //vee_read_operation()
#include "defenitions.h"
#include "s1_button.h"
/* Boolean flag to determine switch is pressed or not.*/
static volatile uint8_t button_press = 0;

fsp_err_t icu_s1_open(void)
{

    fsp_err_t err = FSP_SUCCESS;
    /* Open ICU module */
    err = R_ICU_ExternalIrqOpen(&s1_button_irq_ctrl, &s1_button_irq_cfg);
    /* Print error */
    if (FSP_SUCCESS != err)
    {
        /* ICU Open failure message */
        APP_ERR_PRINT("\r\n**R_ICU_ExternalIrqOpen API FAILED**\r\n");
    }

    return err;
}

fsp_err_t icu_s1_enable(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Enable ICU module */
    err = R_ICU_ExternalIrqEnable(&s1_button_irq_ctrl);

    /* Print error */
    if (FSP_SUCCESS != err)
    {
        /* ICU Enable failure message */
        APP_ERR_PRINT("\r\n**R_ICU_ExternalIrqEnable API FAILED**\r\n");
    }
    return err;
}

void irq_s1_cb(external_irq_callback_args_t *p_args)
{
    button_press++;
    switch (button_press)
    {
        case (1):
            //TODO add code stop temperature sensor
            vee_read_operation (TEMPERATURE_ID);
        break;
        case (2):
            //TODO start temperature sensor again
            button_press = 0;
        break;
    }
}

