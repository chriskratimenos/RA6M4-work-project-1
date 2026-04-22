/***********************************************************************************************************************
 * File Name    : hal_entry.c
 * Description  : Main application entry point for temperature monitoring system
 **********************************************************************************************************************/
#include "common_utils.h"
#include "vee_flash.h"
#include "s1_button.h"
#include "s2_button.h"
#include "i2c_sensor.h"
#include "gpt_timer.h"
#include "cmsis_gcc.h"
#include "uart.h"
#include "adc.h"
#include "agt_timer.h"
#define NUM_TEMPERATURE_RECORDINGS 10   //number of temperatures stored
#define TEMPERATURE_ID 0xAA

void initial_temperature_write_to_flash(void);
void peripherals_init(void);

/*Write buffer to write to VEE flash*/
int16_t temperature_write_buffer[NUM_TEMPERATURE_RECORDINGS];
/*Write buffer to read from VEE flash*/
int16_t temperature_read_buffer[NUM_TEMPERATURE_RECORDINGS];
bsp_io_level_t level_LED1 = BSP_IO_LEVEL_LOW;
bsp_io_level_t level_LED2 = BSP_IO_LEVEL_LOW;
bsp_io_level_t level_LED3 = BSP_IO_LEVEL_LOW;

/*******************************************************************************************************************//**
 * @brief  Main application entry point.
 *
 * Initializes all peripherals and runs the main application loop.
 * Handles temperature reading, button events, and low power mode.
 *
 * Features:
 * - Periodic temperature reading from I2C sensor and ADC (averaged)
 * - Storage of temperature data to Virtual EEPROM
 * - S1 button: Toggle between reading mode and display mode
 * - S2 button: Enter low power mode
 * - UART output of temperature data
 **********************************************************************************************************************/
void hal_entry(void)
{
    /*Initialize the peripherals*/
    peripherals_init ();
    int16_t sensor_temp, adc_temp;
    /*variable to check FSM state when S1 is pressed*/
    int state = 0;
    uint8_t idx = 0;
    /*Start the GPT timer*/
    start_gpt_timer ();
    while (1)
    {
        /*Handle Timer overflow every 1 sec*/
        if (g_timer_overflow == true)
        {
            /*Toggle LED1 when reading*/
            level_LED1 = (level_LED1) ? BSP_IO_LEVEL_LOW : BSP_IO_LEVEL_HIGH;
            R_IOPORT_PinWrite (&g_ioport_ctrl, LED1, level_LED1);
            sensor_temp = read_sensor_data ();
            adc_temp = adc_scan_read ();
            /*Average the 2 values*/
            temperature_write_buffer[idx] = (int16_t) ((sensor_temp + adc_temp) >> 1);
            /* Write to UART console*/
            uart_write (&temperature_write_buffer[idx], sizeof(temperature_write_buffer[0]));
            /* If the read buffer is full, write them to VEEPROM*/
            idx++;
            if (idx == NUM_TEMPERATURE_RECORDINGS)
            {
                vee_write_operation (TEMPERATURE_ID, temperature_write_buffer, 2 * NUM_TEMPERATURE_RECORDINGS);
                /*Clear write buffer*/
                memset (temperature_write_buffer, 0, NUM_TEMPERATURE_RECORDINGS * sizeof(temperature_write_buffer[0]));
                idx = 0;
            }
            g_timer_overflow = false;

        }
        /*2-state FSM for S1 button press states*/
        else if (g_s1_button_pressed == true)
        {
            switch (state)
            {
                /* S1 is first pressed:
                 * 1) Stop the GTP timer to disable temperature reading
                 * 2) Read from VEEPROM temperatures
                 * 3) Print temperatures to UART
                 * */
                case (0):
                    stop_gpt_timer ();
                    /*Set the LEDs*/
                    R_IOPORT_PinWrite (&g_ioport_ctrl, LED1, BSP_IO_LEVEL_LOW);
                    R_IOPORT_PinWrite (&g_ioport_ctrl, LED2, BSP_IO_LEVEL_HIGH);
                    g_s1_button_pressed = false;
                    /*Read from VEE FLASH*/
                    vee_read_operation (TEMPERATURE_ID, temperature_read_buffer, 2 * NUM_TEMPERATURE_RECORDINGS);
                    /*Write to UART*/
                    uart_write (temperature_read_buffer,
                    NUM_TEMPERATURE_RECORDINGS * sizeof(temperature_read_buffer[0]));
                    state++;
                break;
                case (1):
                    /*Clear read buffer*/
                    memset (temperature_read_buffer, 0,
                    NUM_TEMPERATURE_RECORDINGS * sizeof(temperature_read_buffer[0]));
                    /*Return the FSM to starting state*/
                    g_s1_button_pressed = false;
                    state = 0;
                    R_IOPORT_PinWrite (&g_ioport_ctrl, LED2, BSP_IO_LEVEL_LOW);
                    /*Start the GTP timer to start temperature readings again*/
                    start_gpt_timer ();
                break;
            }
        }
        else if (g_s2_button_pressed == true)
        {
            fsp_err_t err = FSP_SUCCESS;
            R_IOPORT_PinWrite (&g_ioport_ctrl, LED1, BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite (&g_ioport_ctrl, LED2, BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite (&g_ioport_ctrl, LED3, BSP_IO_LEVEL_HIGH);
            stop_gpt_timer ();
            start_agt_timer ();
            err = R_LPM_LowPowerModeEnter (&g_lpm0_ctrl);
            if (FSP_SUCCESS != err)
            {
                /* ICU Enable failure message */
                APP_ERR_PRINT("\r\n**R_LPM_LowPowerModeEnter API FAILED**\r\n");
                APP_ERR_TRAP(err);
            }
            R_IOPORT_PinWrite (&g_ioport_ctrl, LED1, BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite (&g_ioport_ctrl, LED2, BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite (&g_ioport_ctrl, LED3, BSP_IO_LEVEL_LOW);
            start_gpt_timer ();
            g_s2_button_pressed = false;
        }
    }
}

/*******************************************************************************************************************//**
 * @brief  Initialize all peripherals.
 *
 * Initializes and configures all required peripherals:
 * - GPT and AGT timers
 * - S1 and S2 button interrupts
 * - VEE Flash for persistent storage
 * - I2C temperature sensor (MCP9808)
 * - ADC for internal temperature sensor
 * - UART for serial communication
 * - Low Power Mode
 *
 * Must be called once at startup before main loop.
 **********************************************************************************************************************/
void peripherals_init(void)
{
    /* Initialize GPT timer*/
    init_gpt_timer ();
    /* Initialize AGT timer*/
    init_agt_timer ();
    /* Initialize & Open S1 & S2 button*/
    icu_s1_open ();
    icu_s1_enable ();
    icu_s2_open ();
    icu_s2_enable ();
    /*Initialize and Format the VEE FLASH*/
    vee_flash_init ();
    vee_format_operation ();
    /* Initialize Temperature Sensor*/
    init_sensor ();
    /*Initialize & Calibrate the ADC temperature*/
    adc_init ();
    adc_calibrate ();
    /* Initialize UART*/
    uart_init ();
    /*Enable Low Power Mode*/
    fsp_err_t err = FSP_SUCCESS;
    err = R_LPM_Open (&g_lpm0_ctrl, &g_lpm0_cfg);
    APP_ERR_TRAP(err);
    /*Start ADC temperature sensor*/
    initial_temperature_write_to_flash ();
    return;
}

/*******************************************************************************************************************//**
 * @brief  Perform initial temperature readings and write to flash.
 *
 * Reads temperature data from sensor to fill the buffer and writes
 * initial values to VEE Flash. Called once during initialization.
 **********************************************************************************************************************/
void initial_temperature_write_to_flash(void)
{
    for (int i = 0; i < NUM_TEMPERATURE_RECORDINGS; i++)
    {
        temperature_write_buffer[i] = read_sensor_data ();
    }
    vee_write_operation (TEMPERATURE_ID, temperature_write_buffer, 2 * NUM_TEMPERATURE_RECORDINGS);
    memset (temperature_write_buffer, 0, sizeof(temperature_write_buffer));
}

