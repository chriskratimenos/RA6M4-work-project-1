/***********************************************************************************************************************
 * File Name    : gpt_timer.c
 * Description  : GPT timer operations for periodic timing functionality
 **********************************************************************************************************************/
#include "common_utils.h"
#include "gpt_timer.h"
/* Global flag to indicate timer overflow */
volatile bool g_timer_overflow = false;

/*******************************************************************************************************************//**
 * @brief  Initialize the GPT timer module.
 *
 * Opens and initializes the GPT timer driver.
 * Must be called before starting the timer.
 **********************************************************************************************************************/
void init_gpt_timer(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Initialize GPT Timer */
    err = R_GPT_Open (&g_timer_ctrl, &g_timer_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_GPT_TimerOpen FAILED ** \r\n");
        APP_ERR_TRAP(err);
    }
    return;
}

/*******************************************************************************************************************//**
 * @brief  Start the GPT timer.
 *
 * Starts the GPT timer to begin counting.
 * Must be called after init_gpt_timer.
 **********************************************************************************************************************/
void start_gpt_timer()
{
    fsp_err_t err = FSP_SUCCESS;
    /* Starts GPT timer */
    err = R_GPT_Start (&g_timer_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_GPT_Start API failed ** \r\n");
        APP_ERR_TRAP(err);
    }
    return;
}

/*******************************************************************************************************************//**
 * @brief  Stop the GPT timer.
 *
 * Stops the GPT timer from counting.
 **********************************************************************************************************************/
void stop_gpt_timer()
{
    fsp_err_t err = FSP_SUCCESS;
    /* Stops GPT timer */
    err = R_GPT_Stop (&g_timer_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_GPT_Stop API failed ** \r\n");
        APP_ERR_TRAP(err);
    }
    return;
}

/*******************************************************************************************************************//**
 * @brief  Callback function for GPT timer overflow.
 *
 * Called by the GPT driver when timer overflow occurs.
 * Sets a flag to indicate timer overflow event.
 *
 * @param[in]  p_args  Pointer to callback arguments containing the timer event
 **********************************************************************************************************************/
void g_timer_cb(timer_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    g_timer_overflow = true;
}
