/***********************************************************************************************************************
 * File Name    : s2_button.c
 * Description  : S2 button interrupt handling using ICU external IRQ
 **********************************************************************************************************************/
#include "common_utils.h"
#include "s2_button.h"
/* This flag is global, is used to determine if the switch is pressed or not.*/
volatile bool g_s2_button_pressed = false;

/*******************************************************************************************************************//**
 * @brief  Open the ICU module for S2 button.
 *
 * Initializes the external IRQ for S2 button press detection.
 * Must be called before enabling the interrupt.
 **********************************************************************************************************************/
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
        APP_ERR_TRAP(err);
    }

    return ;
}

/*******************************************************************************************************************//**
 * @brief  Enable the ICU interrupt for S2 button.
 *
 * Enables the external IRQ to start detecting S2 button presses.
 * Must be called after icu_s2_open.
 **********************************************************************************************************************/
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
        APP_ERR_TRAP(err);
    }
    return;
}

/*******************************************************************************************************************//**
 * @brief  Callback function for S2 button interrupt.
 *
 * Called by the ICU driver when S2 button is pressed.
 * Sets a flag to indicate button press event.
 *
 * @param[in]  p_args  Pointer to callback arguments containing the IRQ event
 **********************************************************************************************************************/
void irq_s2_cb(external_irq_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    g_s2_button_pressed = true;
    return;
}

