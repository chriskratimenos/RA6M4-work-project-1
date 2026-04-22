/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = fcu_frdyi_isr, /* FCU FRDYI (Flash ready interrupt) */
            [1] = fcu_fiferr_isr, /* FCU FIFERR (Flash access error interrupt) */
            [2] = r_icu_isr, /* ICU IRQ10 (External pin interrupt 10) */
            [3] = agt_int_isr, /* AGT1 INT (AGT interrupt) */
            [4] = r_icu_isr, /* ICU IRQ11 (External pin interrupt 11) */
            [5] = iic_master_rxi_isr, /* IIC1 RXI (Receive data full) */
            [6] = iic_master_txi_isr, /* IIC1 TXI (Transmit data empty) */
            [7] = iic_master_tei_isr, /* IIC1 TEI (Transmit end) */
            [8] = iic_master_eri_isr, /* IIC1 ERI (Transfer error) */
            [9] = gpt_counter_overflow_isr, /* GPT6 COUNTER OVERFLOW (Overflow) */
            [10] = sci_uart_rxi_isr, /* SCI0 RXI (Receive data full) */
            [11] = sci_uart_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [12] = sci_uart_tei_isr, /* SCI0 TEI (Transmit end) */
            [13] = sci_uart_eri_isr, /* SCI0 ERI (Receive error) */
            [14] = adc_scan_end_isr, /* ADC0 SCAN END (End of A/D scanning operation) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_FCU_FRDYI,GROUP0), /* FCU FRDYI (Flash ready interrupt) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_FCU_FIFERR,GROUP1), /* FCU FIFERR (Flash access error interrupt) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ10,GROUP2), /* ICU IRQ10 (External pin interrupt 10) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_AGT1_INT,GROUP3), /* AGT1 INT (AGT interrupt) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ11,GROUP4), /* ICU IRQ11 (External pin interrupt 11) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_IIC1_RXI,GROUP5), /* IIC1 RXI (Receive data full) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_IIC1_TXI,GROUP6), /* IIC1 TXI (Transmit data empty) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_IIC1_TEI,GROUP7), /* IIC1 TEI (Transmit end) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_IIC1_ERI,GROUP0), /* IIC1 ERI (Transfer error) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_GPT6_COUNTER_OVERFLOW,GROUP1), /* GPT6 COUNTER OVERFLOW (Overflow) */
            [10] = BSP_PRV_VECT_ENUM(EVENT_SCI0_RXI,GROUP2), /* SCI0 RXI (Receive data full) */
            [11] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TXI,GROUP3), /* SCI0 TXI (Transmit data empty) */
            [12] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TEI,GROUP4), /* SCI0 TEI (Transmit end) */
            [13] = BSP_PRV_VECT_ENUM(EVENT_SCI0_ERI,GROUP5), /* SCI0 ERI (Receive error) */
            [14] = BSP_PRV_VECT_ENUM(EVENT_ADC0_SCAN_END,GROUP6), /* ADC0 SCAN END (End of A/D scanning operation) */
        };
        #endif
        #endif
