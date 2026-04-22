/***********************************************************************************************************************
 * File Name    : agt_timer.c
 * Description  : AGT timer operations for periodic timing functionality
 **********************************************************************************************************************/
#include "common_utils.h"
#include "agt_timer.h"

 /*******************************************************************************************************************//**
  * @brief  Initialize the AGT timer module.
  *
  * Opens and initializes the AGT timer driver.
  * Must be called before starting the timer.
  **********************************************************************************************************************/
void init_agt_timer(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Initialize AGT Timer */
    err = R_AGT_Open (&agt_timer_ctrl, &agt_timer_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_AGT_Open FAILED ** \r\n");
        APP_ERR_TRAP(err);
    }
    return;
}

/*******************************************************************************************************************//**
 * @brief  Start the AGT timer.
 *
 * Starts the AGT timer to begin counting.
 * Must be called after init_agt_timer.
 **********************************************************************************************************************/
void start_agt_timer(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Starts AGT timer */
    err = R_AGT_Start (&agt_timer_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_AGT_Start API failed ** \r\n");
        APP_ERR_TRAP(err);
    }
    return;
}

/*******************************************************************************************************************//**
 * @brief  Stop the AGT timer.
 *
 * Stops the AGT timer from counting.
 **********************************************************************************************************************/
void stop_agt_timer(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Stop AGT timer */
    err = R_AGT_Stop (&agt_timer_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_AGT_Stop API failed ** \r\n");
        APP_ERR_TRAP(err);
    }
    return;
}

