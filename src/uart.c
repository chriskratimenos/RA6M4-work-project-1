#include "common_utils.h"
#include "hal_data.h"
#include "uart.h"
volatile bool g_uart9_tx_flag = false;
/* Callback function */
void g_uart_cb(uart_callback_args_t *p_args)
{
    switch (p_args->event)
    {
        case UART_EVENT_TX_COMPLETE:
        {
            g_uart9_tx_flag = true;
            break;
        }

        case UART_EVENT_TX_DATA_EMPTY:
        {
            /* ⚠️ FIFO empty but NOT done */
            /* Do NOT set flag here!      */
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

void uart_init()
{
    fsp_err_t err = FSP_SUCCESS;
    /* Initialize the UART */
    err = R_SCI_UART_Open (&g_uart_ctrl, &g_uart_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_SCI_UART_Open FAILED ** \r\n");
    }
    return;

}

void uart_write(void *p_src, uint32_t num_bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_SCI_UART_Write (&g_uart_ctrl, p_src, num_bytes);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_SCI_UART_Write FAILED ** \r\n");
    }
    while (g_uart9_tx_flag != true)
    {
        ;
    }
    g_uart9_tx_flag = false;
    return;
}
