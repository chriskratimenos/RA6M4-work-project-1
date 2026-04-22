#include "common_utils.h"
#include "vee_flash.h"
#include "s1_button.h"
/* Boolean flag to determine switch is pressed or not.*/

volatile bool s1_button_pressed = false;
void icu_s1_open(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Open ICU module */
    err = R_ICU_ExternalIrqOpen (&s1_button_irq_ctrl, &s1_button_irq_cfg);
    /* Print error */
    if (FSP_SUCCESS != err)
    {
        /* ICU Open failure message */
        APP_ERR_PRINT("\r\n**R_ICU_ExternalIrqOpen API FAILED**\r\n");
    }
    return;
}

void icu_s1_enable(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Enable ICU module */
    err = R_ICU_ExternalIrqEnable (&s1_button_irq_ctrl);

    /* Print error */
    if (FSP_SUCCESS != err)
    {
        /* ICU Enable failure message */
        APP_ERR_PRINT("\r\n**R_ICU_ExternalIrqEnable API FAILED**\r\n");
    }
    return ;
}

void irq_s1_cb(external_irq_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    s1_button_pressed = true;
    return ;
}

