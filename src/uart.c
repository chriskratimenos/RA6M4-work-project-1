/***********************************************************************************************************************
 * File Name    : uart.c
 * Description  : UART communication operations for serial data transmission
 **********************************************************************************************************************/
#include "common_utils.h"
#include "uart.h"
volatile bool uart_tx_flag = false;

/*******************************************************************************************************************//**
 * @brief  Initialize the UART module.
 *
 * Opens and initializes the SCI UART driver for serial communication.
 * Must be called before any other UART operations.
 **********************************************************************************************************************/
void uart_init()
{
    fsp_err_t err = FSP_SUCCESS;
    /* Initialize the UART */
    err = R_SCI_UART_Open (&g_uart_ctrl, &g_uart_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_SCI_UART_Open FAILED ** \r\n");
        APP_ERR_TRAP(err);
    }
    return;
}

/*******************************************************************************************************************//**
 * @brief  Write data over UART.
 *
 * Transmits the specified data over UART.
 * This function blocks until the transmission completes via callback.
 *
 * @param[in]  p_src      Pointer to the data buffer to transmit
 * @param[in]  num_bytes  Number of bytes to transmit
 **********************************************************************************************************************/
void uart_write(void *p_src, uint32_t num_bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_SCI_UART_Write (&g_uart_ctrl, p_src, num_bytes);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_SCI_UART_Write FAILED ** \r\n");
        APP_ERR_TRAP(err);
    }
    while (uart_tx_flag != true)
    {
        ;
    }
    uart_tx_flag = false;
    return;
}

/*******************************************************************************************************************//**
 * @brief  Callback function for UART operations.
 *
 * Called by the UART driver when a UART event occurs.
 * Handles TX complete, TX data empty, and RX character events.
 *
 * @param[in]  p_args  Pointer to callback arguments containing the UART event
 **********************************************************************************************************************/
void g_uart_cb(uart_callback_args_t *p_args)
{
    switch (p_args->event)
    {
        case UART_EVENT_TX_COMPLETE:
        {
            uart_tx_flag = true;
            break;
        }
        case UART_EVENT_TX_DATA_EMPTY:
        {
            break;
        }
        case UART_EVENT_RX_CHAR:
        {
            break;
        }

        default:
        {
            break;
        }
    }
}
