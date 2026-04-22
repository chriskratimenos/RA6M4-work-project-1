#include "common_utils.h"
#include "s2_button.h"
/* Boolean flag to determine switch is pressed or not.*/
volatile bool s2_button_pressed = false;

void icu_s2_open(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Open ICU module */
    err = R_ICU_ExternalIrqOpen (&s2_button_irq_ctrl, &s2_button_irq_cfg);
    /* Print error */
    if (FSP_SUCCESS != err)
    {
        /* ICU Open failure message */
        APP_ERR_PRINT("\r\n**R_ICU_ExternalIrqOpen API FAILED**\r\n");
    }

    return ;
}

void icu_s2_enable(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Enable ICU module */
    err = R_ICU_ExternalIrqEnable (&s2_button_irq_ctrl);
    /* Print error */
    if (FSP_SUCCESS != err)
    {
        /* ICU Enable failure message */
        APP_ERR_PRINT("\r\n**R_ICU_ExternalIrqEnable API FAILED**\r\n");
    }
    return;
}

void irq_s2_cb(external_irq_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    s2_button_pressed = true;
    return;
}

