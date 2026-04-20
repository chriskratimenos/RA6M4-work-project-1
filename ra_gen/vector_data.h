/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (4)
#endif
/* ISR prototypes */
void fcu_frdyi_isr(void);
void fcu_fiferr_isr(void);
void r_icu_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_FCU_FRDYI ((IRQn_Type) 0) /* FCU FRDYI (Flash ready interrupt) */
#define FCU_FRDYI_IRQn          ((IRQn_Type) 0) /* FCU FRDYI (Flash ready interrupt) */
#define VECTOR_NUMBER_FCU_FIFERR ((IRQn_Type) 1) /* FCU FIFERR (Flash access error interrupt) */
#define FCU_FIFERR_IRQn          ((IRQn_Type) 1) /* FCU FIFERR (Flash access error interrupt) */
#define VECTOR_NUMBER_ICU_IRQ10 ((IRQn_Type) 2) /* ICU IRQ10 (External pin interrupt 10) */
#define ICU_IRQ10_IRQn          ((IRQn_Type) 2) /* ICU IRQ10 (External pin interrupt 10) */
#define VECTOR_NUMBER_ICU_IRQ11 ((IRQn_Type) 3) /* ICU IRQ11 (External pin interrupt 11) */
#define ICU_IRQ11_IRQn          ((IRQn_Type) 3) /* ICU IRQ11 (External pin interrupt 11) */
/* The number of entries required for the ICU vector table. */
#define BSP_ICU_VECTOR_NUM_ENTRIES (4)

#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
