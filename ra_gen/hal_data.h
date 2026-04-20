/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_iic_master.h"
#include "r_i2c_master_api.h"
#include "r_lpm.h"
#include "r_lpm_api.h"
#include "r_agt.h"
#include "r_timer_api.h"
#include "r_flash_hp.h"
#include "r_flash_api.h"
#include "rm_vee_flash.h"
FSP_HEADER
/* I2C Master on IIC Instance. */
extern const i2c_master_instance_t g_i2c_master;

/** Access the I2C Master instance using these structures when calling API functions directly (::p_api is not used). */
extern iic_master_instance_ctrl_t g_i2c_master_ctrl;
extern const i2c_master_cfg_t g_i2c_master_cfg;

#ifndef i2c_master_callback
void i2c_master_callback(i2c_master_callback_args_t *p_args);
#endif
/** lpm Instance */
extern const lpm_instance_t g_lpm0;

/** Access the LPM instance using these structures when calling API functions directly (::p_api is not used). */
extern lpm_instance_ctrl_t g_lpm0_ctrl;
extern const lpm_cfg_t g_lpm0_cfg;
/** AGT Timer Instance */
extern const timer_instance_t g_timer0;

/** Access the AGT instance using these structures when calling API functions directly (::p_api is not used). */
extern agt_instance_ctrl_t g_timer0_ctrl;
extern const timer_cfg_t g_timer0_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
/* Flash on Flash HP Instance */
extern const flash_instance_t g_flash0;

/** Access the Flash HP instance using these structures when calling API functions directly (::p_api is not used). */
extern flash_hp_instance_ctrl_t g_flash0_ctrl;
extern const flash_cfg_t g_flash0_cfg;

#ifndef rm_vee_flash_callback
void rm_vee_flash_callback(flash_callback_args_t *p_args);
#endif
extern const rm_vee_instance_t g_vee;
extern rm_vee_flash_instance_ctrl_t g_vee_ctrl;
extern const rm_vee_cfg_t g_vee_cfg;

/** Callback used by VEE Instance. */
#ifndef vee_callback
void vee_callback(rm_vee_callback_args_t *p_args);
#endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
