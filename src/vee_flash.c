#include "hal_data.h"
#include "cmsis_gcc.h"
#include <string.h>
#include "vee_flash.h"
#include "common_utils.h"
static bool callback_called = false;
static rm_vee_state_t vee_done_state;
uint8_t read_buffer[16];    //global read buffer that contains temperature array

/* Callback function */
void vee_callback(rm_vee_callback_args_t *p_args)
{
    callback_called = true;
    vee_done_state = p_args->state;
}

/*Initialize the VEE_FLASH module*/
fsp_err_t vee_flash_init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Open the RM_VEE_FLASH driver module.*/
    err = RM_VEE_FLASH_Open (&g_vee_ctrl, &g_vee_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_Open API FAILED **\r\n");
    }
    return err;
}

fsp_err_t vee_format_operation(void)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t ref_data = RESET_VALUE;
    /* Start a manual format operation.*/
    err = RM_VEE_FLASH_Format (&g_vee_ctrl, &ref_data);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_Format API FAILED **\r\n");
        return err;
    }
    /* Get the current status of the driver.*/
    rm_vee_status_t p_status;
    err = RM_VEE_FLASH_StatusGet (&g_vee_ctrl, &p_status);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_StatusGet API FAILED **\r\n");
        return err;
    }
    /* Compare Last ID written with Default ID.*/
    return err;
}

fsp_err_t vee_write_operation(uint32_t const rec_id, void *p_rec_data, uint32_t num_bytes)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Write the data to a Virtual EEPROM Record. */
    err = RM_VEE_FLASH_RecordWrite (&g_vee_ctrl, rec_id, p_rec_data, num_bytes);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n** RM_VEE_FLASH_Open FAILED **\r\n");
        return err;
    }
    /*Wait for Virtual EEPROM callback to indicate that it has finished writing data and vee flash is in a ready state*/
    while (callback_called != true)
    {
        //TODO handle if it takes to long with a watchdog timer
        ;
    }
    /* Reset the flag.*/
    callback_called = false;
    return err;
}

fsp_err_t vee_read_operation(uint32_t const rec_id)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t num_bytes;
    uint8_t * p_record_data;
    /* Get a pointer to the record that is stored in data flash. */
    err = RM_VEE_FLASH_RecordPtrGet (&g_vee_ctrl, rec_id, (uint8_t**) &p_record_data, &num_bytes);
    memcpy(read_buffer, p_record_data, num_bytes);
    return err;
}

