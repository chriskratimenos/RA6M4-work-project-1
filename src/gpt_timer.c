#include "hal_data.h"
#include "common_utils.h"
#include "cmsis_gcc.h"
#include "gpt_timer.h"
volatile bool timer_overflow = false;


void init_gpt_timer(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Initialize GPT Timer */
    err = R_GPT_Open (&g_timer_ctrl, &g_timer_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_GPT_TimerOpen FAILED ** \r\n");
    }
    return;
}

void start_gpt_timer()
{
    fsp_err_t err = FSP_SUCCESS;
    /* Starts GPT timer */
    err = R_GPT_Start (&g_timer_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_GPT_Start API failed ** \r\n");
    }
    return;
}

void stop_gpt_timer()
{
    fsp_err_t err = FSP_SUCCESS;
    /* Starts GPT timer */
    err = R_GPT_Stop (&g_timer_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_GPT_Stop API failed ** \r\n");
    }
    return;
}

/* Callback function */
void g_timer_cb(timer_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    timer_overflow = true;
}
