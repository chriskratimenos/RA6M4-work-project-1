/***********************************************************************************************************************
 * File Name    : vee_flash.c
 * Description  : Virtual EEPROM (VEE) Flash operations for persistent data storage
 **********************************************************************************************************************/
#include "common_utils.h"
#include "vee_flash.h"

/* Flag to indicate VEE callback has been invoked */
static bool callback_called = false;
/* Stores the VEE state returned from callback */

/*******************************************************************************************************************//**
 * @brief  Initialize the VEE Flash module.
 *
 * Opens and initializes the RM_VEE_FLASH driver module for Virtual EEPROM operations.
 * Must be called before any other VEE operations.
 **********************************************************************************************************************/
void vee_flash_init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Open the RM_VEE_FLASH driver module.*/
    err = RM_VEE_FLASH_Open (&g_vee_ctrl, &g_vee_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_Open API FAILED **\r\n");
        APP_ERR_TRAP(err);
    }
    return;
}

/*******************************************************************************************************************//**
 * @brief  Perform a format operation on the VEE Flash.
 *
 * Starts a manual format operation to initialize or reset the Virtual EEPROM storage area.
 *
 * @note  This operation will erase all stored data. Use with caution.
 **********************************************************************************************************************/
void vee_format_operation(void)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t ref_data = RESET_VALUE;
    /* Start a manual format operation.*/
    err = RM_VEE_FLASH_Format (&g_vee_ctrl, &ref_data);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_Format API FAILED **\r\n");
        APP_ERR_TRAP(err);
        return;
    }
    /* Get the current status of the driver.*/
    rm_vee_status_t p_status;
    err = RM_VEE_FLASH_StatusGet (&g_vee_ctrl, &p_status);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_StatusGet API FAILED **\r\n");
        APP_ERR_TRAP(err);
        return;
    }
    return;
}

/*******************************************************************************************************************//**
 * @brief  Write data to a VEE Flash record.
 *
 * Writes the specified data to a Virtual EEPROM record identified by the record ID.
 * This function blocks until the write operation completes via callback.
 *
 * @param[in]  rec_id       Record ID to write to
 * @param[in]  p_rec_data   Pointer to the data buffer to write
 * @param[in]  num_bytes    Number of bytes to write
 **********************************************************************************************************************/
void vee_write_operation(uint32_t const rec_id, void *p_rec_data, uint32_t num_bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Write the data to a Virtual EEPROM Record. */
    err = RM_VEE_FLASH_RecordWrite (&g_vee_ctrl, rec_id, p_rec_data, num_bytes);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_RecordWrite FAILED **\r\n");
        APP_ERR_TRAP(err);
        return;
    }
    /* Wait for Virtual EEPROM callback to indicate that it has finished writing data and VEE flash is in a ready state */
    while (callback_called != true)
    {
        ;
    }
    /* Reset the flag.*/
    callback_called = false;
    return;
}

/*******************************************************************************************************************//**
 * @brief  Read data from a VEE Flash record.
 *
 * Retrieves data from a Virtual EEPROM record and copies it to the provided buffer.
 *
 * @param[in]   rec_id         Record ID to read from
 * @param[out]  p_read_buffer  Pointer to buffer where read data will be stored
 * @param[in]   num_bytes      Maximum number of bytes the buffer can hold
 **********************************************************************************************************************/
void vee_read_operation(uint32_t const rec_id, void *p_read_buffer, uint32_t num_bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t *p_record_data;
    uint32_t record_size;

    /* Get a pointer to the record that is stored in data flash. */
    err = RM_VEE_FLASH_RecordPtrGet (&g_vee_ctrl, rec_id, (uint8_t**) &p_record_data, &record_size);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_RecordPtrGet API FAILED **\r\n");
        APP_ERR_TRAP(err);
        return;
    }
    if (record_size > num_bytes)
    {
        APP_ERR_PRINT("\r\n** Buffer too small **\r\n");
        APP_ERR_TRAP(err);
        return;
    }
    memcpy (p_read_buffer, p_record_data, record_size);
    return;
}

/*******************************************************************************************************************//**
 * @brief  Callback function for VEE Flash operations.
 *
 * Called by the VEE driver when an asynchronous operation completes.
 * Sets a flag to indicate completion.
 *
 * @param[in]  p_args  Pointer to callback arguments containing the VEE state
 **********************************************************************************************************************/
void vee_callback(rm_vee_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    callback_called = true;
}
