/* generated HAL source file - do not edit */
#include "hal_data.h"
#if BSP_TZ_NONSECURE_BUILD
 #if defined(BSP_CFG_CLOCKS_SECURE) && BSP_CFG_CLOCKS_SECURE
  #error "The LPM module requires CGC registers to be non-secure when it is used in a TrustZone Non-secure project."
 #endif
#endif

lpm_instance_ctrl_t g_lpm0_ctrl;

const lpm_cfg_t g_lpm0_cfg =
{ .low_power_mode = LPM_MODE_STANDBY, .standby_wake_sources = LPM_STANDBY_WAKE_SOURCE_IRQ11
        | (lpm_standby_wake_source_t) 0,
#if BSP_FEATURE_ICU_HAS_WUPEN2
    .standby_wake_sources_2     =  (lpm_standby_wake_source_2_t) 0,
#endif
#if BSP_FEATURE_LPM_HAS_SNOOZE
    .snooze_cancel_sources      = LPM_SNOOZE_CANCEL_SOURCE_NONE,
    .snooze_request_source      = (lpm_snooze_request_t) LPM_SNOOZE_REQUEST_RXD0_FALLING,
#if BSP_FEATURE_LPM_SNZEDCR_MASK > 0
    .snooze_end_sources         =  (lpm_snooze_end_t) 0,
#endif
    .dtc_state_in_snooze        = LPM_SNOOZE_DTC_DISABLE,
#endif
#if BSP_FEATURE_LPM_HAS_SBYCR_OPE
    .output_port_enable         = LPM_OUTPUT_PORT_ENABLE_RETAIN,
#endif
#if BSP_FEATURE_LPM_HAS_DEEP_STANDBY
    .io_port_state                = LPM_IO_PORT_NO_CHANGE,
    .power_supply_state           = LPM_POWER_SUPPLY_DEEPCUT0,
    .deep_standby_cancel_source   =  (lpm_deep_standby_cancel_source_t) 0,
    .deep_standby_cancel_edge     =  (lpm_deep_standby_cancel_edge_t) 0,
#if BSP_FEATURE_LPM_HAS_DPSBYCR_DCSSMODE
    .deep_standby_soft_start_mode = 0,
#endif
#endif
#if BSP_FEATURE_LPM_HAS_PDRAMSCR
    .ram_retention_cfg.ram_retention = (uint16_t) ( 0),
    .ram_retention_cfg.tcm_retention = false,
#endif
#if BSP_FEATURE_LPM_HAS_DPSBYCR_SRKEEP
    .ram_retention_cfg.standby_ram_retention = false,
#endif
#if BSP_FEATURE_LPM_HAS_LDO_SKEEP
    .ldo_standby_cfg.pll1_ldo = false,
    .ldo_standby_cfg.pll2_ldo = false,
    .ldo_standby_cfg.hoco_ldo = false,
#endif
#if BSP_FEATURE_LPM_HAS_FLASH_MODE_SELECT
    .lpm_flash_mode_select = false,
#endif
#if BSP_FEATURE_LPM_HAS_HOCO_STARTUP_SPEED_MODE
    .lpm_hoco_startup_speed = false,
#endif
#if BSP_FEATURE_LPM_HAS_STANDBY_SOSC_SELECT
    .lpm_standby_sosc = false,
#endif
  .p_extend = NULL, };

const lpm_instance_t g_lpm0 =
{ .p_api = &g_lpm_on_lpm, .p_ctrl = &g_lpm0_ctrl, .p_cfg = &g_lpm0_cfg };
agt_instance_ctrl_t g_timer0_ctrl;
const agt_extended_cfg_t g_timer0_extend =
{ .count_source = AGT_CLOCK_PCLKB,
  .agto = AGT_PIN_CFG_DISABLED,
  .agtoab_settings_b.agtoa = AGT_PIN_CFG_DISABLED,
  .agtoab_settings_b.agtob = AGT_PIN_CFG_DISABLED,
  .measurement_mode = AGT_MEASURE_DISABLED,
  .agtio_filter = AGT_AGTIO_FILTER_NONE,
  .enable_pin = AGT_ENABLE_PIN_NOT_USED,
  .trigger_edge = AGT_TRIGGER_EDGE_RISING,
  .counter_bit_width = AGT_COUNTER_BIT_WIDTH_16, };
const timer_cfg_t g_timer0_cfg =
{ .mode = TIMER_MODE_PERIODIC,
/* Actual period: 0.00131072 seconds. Actual duty: 50%. */.period_counts = (uint32_t) 0x10000,
  .duty_cycle_counts = 0x8000, .source_div = (timer_source_div_t) 0, .channel = 0, .p_callback = NULL,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = (void*) &NULL,
#endif
  .p_extend = &g_timer0_extend,
  .cycle_end_ipl = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_AGT0_INT)
    .cycle_end_irq       = VECTOR_NUMBER_AGT0_INT,
#else
  .cycle_end_irq = FSP_INVALID_VECTOR,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer0 =
{ .p_ctrl = &g_timer0_ctrl, .p_cfg = &g_timer0_cfg, .p_api = &g_timer_on_agt };
flash_hp_instance_ctrl_t g_flash0_ctrl;
const flash_cfg_t g_flash0_cfg =
{ .data_flash_bgo = true, .p_callback = rm_vee_flash_callback, .p_context = &g_vee_ctrl,
#if defined(VECTOR_NUMBER_FCU_FRDYI)
    .irq                 = VECTOR_NUMBER_FCU_FRDYI,
#else
  .irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_FCU_FIFERR)
    .err_irq             = VECTOR_NUMBER_FCU_FIFERR,
#else
  .err_irq = FSP_INVALID_VECTOR,
#endif
  .err_ipl = (8),
  .ipl = (8), };
/* Instance structure to use this module. */
const flash_instance_t g_flash0 =
{ .p_ctrl = &g_flash0_ctrl, .p_cfg = &g_flash0_cfg, .p_api = &g_flash_on_flash_hp };
rm_vee_flash_instance_ctrl_t g_vee_ctrl;

const rm_vee_flash_cfg_t g_vee_cfg_ext =
{ .p_flash = &g_flash0 };

static uint16_t g_vee_record_offset[2 + 1] =
{ 0 };

const rm_vee_cfg_t g_vee_cfg =
{ .start_addr = BSP_FEATURE_FLASH_DATA_FLASH_START,
  .num_segments = 2,
  .total_size = BSP_DATA_FLASH_SIZE_BYTES,
  .ref_data_size = 0,
  .record_max_id = 2,
  .rec_offset = &g_vee_record_offset[0],
  .p_callback = vee_callback,
  .p_context = NULL,
  .p_extend = &g_vee_cfg_ext };

/* Instance structure to use this module. */
const rm_vee_instance_t g_vee =
{ .p_ctrl = &g_vee_ctrl, .p_cfg = &g_vee_cfg, .p_api = &g_rm_vee_on_flash };
void g_hal_init(void)
{
    g_common_init ();
}
