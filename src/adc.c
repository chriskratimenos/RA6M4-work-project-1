/*
 * adc.c
 *
 *  Created on: 21 Απρ 2026
 *      Author: a5163766
 */
#include "hal_data.h"
#include "common_utils.h"
#include "adc.h"
#define ADC_VCC_MICROVOLT                        (3300000)
#define ADC_TEMPERATURE_RESOLUTION               (12U)
#define ADC_REFERENCE_CALIBRATION_TEMPERATURE    (127)

volatile bool callback_called = false;
int32_t v1_uv;
int32_t slope_uv_per_c = BSP_FEATURE_TSN_SLOPE;

/* This project uses the typical slope provided in Table "TSN characteristics" in the relevant hardware manual. */
/* Formula for calculating temperature copied from section "Preparation for Using the Temperature Sensor"
 * of the relevant hardware manual:
 *
 * In this MCU, the TSCDR register stores the temperature value (CAL127) of the temperature sensor measured
 * under the condition Ta = Tj = 127 C and AVCC0 = 3.3 V. By using this value as the sample measurement result
 * at the first point, preparation before using the temperature sensor can be omitted.
 *
 * If V1 is calculated from CAL127,
 * V1 = 3.3 * CAL127 / 4096 [V]
 *
 * Using this, the measured temperature can be calculated according to the following formula.
 *
 * T = (Vs - V1) / Slope + 127 [C]
 * T: Measured temperature (C)
 * Vs: Voltage output by the temperature sensor when the temperature is measured (V)
 * V1: Voltage output by the temperature sensor when Ta = Tj = 127 C and AVCC0 = 3.3 V (V)
 * Slope: Temperature slope given in Table 52.38 / 1000 (V/C)
 */

void adc_init()
{
    fsp_err_t err = FSP_SUCCESS;
    /* Open and configure the ADC */
    err = R_ADC_Open (&g_adc0_ctrl, &g_adc0_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_ADC_Open FAILED ** \r\n");
    }
    /* Configure ADC channel */
    err = R_ADC_ScanCfg (&g_adc0_ctrl, &g_adc0_channel_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_ADC_ScanCfg FAILED ** \r\n");
    }
    return;
}


int16_t adc_scan_read()
{
    fsp_err_t err = FSP_SUCCESS;
    /* Start ADC scan */
    err = R_ADC_ScanStart (&g_adc0_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_ADC_ScanCfg FAILED ** \r\n");
    }
    while (callback_called != true)
    {

    }
    callback_called = false;
    /*Read from the ADC*/
    uint16_t temperature_conversion_result;
    err = R_ADC_Read (&g_adc0_ctrl, ADC_CHANNEL_TEMPERATURE, &temperature_conversion_result);
    int32_t vs_uv = (ADC_VCC_MICROVOLT >> ADC_TEMPERATURE_RESOLUTION) * temperature_conversion_result;
    int16_t  adc_temperature = (vs_uv - v1_uv) / slope_uv_per_c + ADC_REFERENCE_CALIBRATION_TEMPERATURE;
    return adc_temperature;
}

void adc_calibrate()
{
    adc_status_t adc_status;         // to get adc status
    fsp_err_t err = FSP_SUCCESS;
    /* Calibrate ADC scan */
    err = R_ADC_Calibrate (&g_adc0_ctrl, NULL);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n ** R_ADC_ScanCfg FAILED ** \r\n");
    }
    do
    {
        /* To get the adc status*/
        err = R_ADC_StatusGet (&g_adc0_ctrl, &adc_status);

        /* handle error */
        if (FSP_SUCCESS != err)
        {
            /* ADC status Failure message */
            APP_ERR_PRINT("** R_ADC_StatusGet API failed ** \r\n");
            return;
        }
    }
    while (ADC_STATE_IDLE != adc_status.state); //wait here till the calibration.It takes 24msec to 780msec based on clock
    /* Get Calibration data from the MCU if available. */
    int32_t reference_calibration_data;
    adc_info_t adc_info;
    (void) R_ADC_InfoGet (&g_adc0_ctrl, &adc_info);
    reference_calibration_data = (int32_t) adc_info.calibration_data;
    v1_uv = (ADC_VCC_MICROVOLT >> ADC_TEMPERATURE_RESOLUTION) * reference_calibration_data;
    return;

}

/* Callback function */
void adc_cb(adc_callback_args_t *p_args)
{
    callback_called = true;
}
