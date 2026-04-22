/*
 * agt_timer.c
 *
 *  Created on: 22 Απρ 2026
 *      Author: a5163766
 */
#include "hal_data.h"
#include "common_utils.h"


void init_agt_timer(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Initialize AGT Timer */
    err = R_AGT_Open(&agt_timer_ctrl, &agt_timer_cfg);
        if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_GPT_TimerOpen FAILED ** \r\n");
    }
    return;
}

void start_agt_timer()
{
    fsp_err_t err = FSP_SUCCESS;
    /* Starts AGT timer */
    err = R_AGT_Start(&agt_timer_ctrl);
        if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_AGT_Start API failed ** \r\n");
    }
    return;
}

void stop_agt_timer()
{
    fsp_err_t err = FSP_SUCCESS;
    /* Starts AGT timer */
    err = R_AGT_Stop(&agt_timer_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_AGT_Stop API failed ** \r\n");
    }
    return;
}

