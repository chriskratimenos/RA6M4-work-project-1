/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = fcu_frdyi_isr, /* FCU FRDYI (Flash ready interrupt) */
            [1] = fcu_fiferr_isr, /* FCU FIFERR (Flash access error interrupt) */
            [2] = r_icu_isr, /* ICU IRQ10 (External pin interrupt 10) */
            [3] = r_icu_isr, /* ICU IRQ11 (External pin interrupt 11) */
            [4] = iic_master_rxi_isr, /* IIC1 RXI (Receive data full) */
            [5] = iic_master_txi_isr, /* IIC1 TXI (Transmit data empty) */
            [6] = iic_master_tei_isr, /* IIC1 TEI (Transmit end) */
            [7] = iic_master_eri_isr, /* IIC1 ERI (Transfer error) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_FCU_FRDYI,GROUP0), /* FCU FRDYI (Flash ready interrupt) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_FCU_FIFERR,GROUP1), /* FCU FIFERR (Flash access error interrupt) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ10,GROUP2), /* ICU IRQ10 (External pin interrupt 10) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ11,GROUP3), /* ICU IRQ11 (External pin interrupt 11) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_IIC1_RXI,GROUP4), /* IIC1 RXI (Receive data full) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_IIC1_TXI,GROUP5), /* IIC1 TXI (Transmit data empty) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_IIC1_TEI,GROUP6), /* IIC1 TEI (Transmit end) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_IIC1_ERI,GROUP7), /* IIC1 ERI (Transfer error) */
        };
        #endif
        #endif
