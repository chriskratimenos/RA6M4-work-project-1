#include "hal_data.h"
#include "cmsis_gcc.h"
#include <string.h>
#include "vee_flash.h"
#include "common_utils.h"
static bool callback_called = false;
static rm_vee_state_t vee_done_state;
//global read buffer that contains temperature array

/* Callback function */
void vee_callback(rm_vee_callback_args_t *p_args)
{
    callback_called = true;
    vee_done_state = p_args->state;
}

/*Initialize the VEE_FLASH module*/
void vee_flash_init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Open the RM_VEE_FLASH driver module.*/
    err = RM_VEE_FLASH_Open (&g_vee_ctrl, &g_vee_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_Open API FAILED **\r\n");
    }
    return ;
}

void  vee_format_operation(void)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t ref_data = RESET_VALUE;
    /* Start a manual format operation.*/
    err = RM_VEE_FLASH_Format (&g_vee_ctrl, &ref_data);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_Format API FAILED **\r\n");
        return ;
    }
    /* Get the current status of the driver.*/
    rm_vee_status_t p_status;
    err = RM_VEE_FLASH_StatusGet (&g_vee_ctrl, &p_status);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_StatusGet API FAILED **\r\n");
        return ;
    }
    /* Compare Last ID written with Default ID.*/
    return ;
}

void vee_write_operation(uint32_t const rec_id, void *p_rec_data, uint32_t num_bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Write the data to a Virtual EEPROM Record. */
    err = RM_VEE_FLASH_RecordWrite (&g_vee_ctrl, rec_id, p_rec_data, num_bytes);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_Open FAILED **\r\n");
        return ;
    }
    /*Wait for Virtual EEPROM callback to indicate that it has finished writing data and vee flash is in a ready state*/
    while (callback_called != true)
    {
        //TODO handle if it takes to long with a watchdog timer
        ;
    }
    /* Reset the flag.*/
    callback_called = false;
    return ;
}

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
        return err;
    }
    if (record_size > num_bytes)
    {
        return FSP_ERR_INVALID_SIZE;
    }
    memcpy (p_read_buffer, p_record_data, record_size);
    return ;
}

