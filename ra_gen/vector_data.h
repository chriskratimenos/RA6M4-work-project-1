/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (8)
#endif
/* ISR prototypes */
void fcu_frdyi_isr(void);
void fcu_fiferr_isr(void);
void r_icu_isr(void);
void iic_master_rxi_isr(void);
void iic_master_txi_isr(void);
void iic_master_tei_isr(void);
void iic_master_eri_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_FCU_FRDYI ((IRQn_Type) 0) /* FCU FRDYI (Flash ready interrupt) */
#define FCU_FRDYI_IRQn          ((IRQn_Type) 0) /* FCU FRDYI (Flash ready interrupt) */
#define VECTOR_NUMBER_FCU_FIFERR ((IRQn_Type) 1) /* FCU FIFERR (Flash access error interrupt) */
#define FCU_FIFERR_IRQn          ((IRQn_Type) 1) /* FCU FIFERR (Flash access error interrupt) */
#define VECTOR_NUMBER_ICU_IRQ10 ((IRQn_Type) 2) /* ICU IRQ10 (External pin interrupt 10) */
#define ICU_IRQ10_IRQn          ((IRQn_Type) 2) /* ICU IRQ10 (External pin interrupt 10) */
#define VECTOR_NUMBER_ICU_IRQ11 ((IRQn_Type) 3) /* ICU IRQ11 (External pin interrupt 11) */
#define ICU_IRQ11_IRQn          ((IRQn_Type) 3) /* ICU IRQ11 (External pin interrupt 11) */
#define VECTOR_NUMBER_IIC1_RXI ((IRQn_Type) 4) /* IIC1 RXI (Receive data full) */
#define IIC1_RXI_IRQn          ((IRQn_Type) 4) /* IIC1 RXI (Receive data full) */
#define VECTOR_NUMBER_IIC1_TXI ((IRQn_Type) 5) /* IIC1 TXI (Transmit data empty) */
#define IIC1_TXI_IRQn          ((IRQn_Type) 5) /* IIC1 TXI (Transmit data empty) */
#define VECTOR_NUMBER_IIC1_TEI ((IRQn_Type) 6) /* IIC1 TEI (Transmit end) */
#define IIC1_TEI_IRQn          ((IRQn_Type) 6) /* IIC1 TEI (Transmit end) */
#define VECTOR_NUMBER_IIC1_ERI ((IRQn_Type) 7) /* IIC1 ERI (Transfer error) */
#define IIC1_ERI_IRQn          ((IRQn_Type) 7) /* IIC1 ERI (Transfer error) */
/* The number of entries required for the ICU vector table. */
#define BSP_ICU_VECTOR_NUM_ENTRIES (8)

#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
