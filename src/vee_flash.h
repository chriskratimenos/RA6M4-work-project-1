#ifndef VEE_FLASH_H_
#define VEE_FLASH_H_

fsp_err_t vee_flash_init(void);
fsp_err_t vee_format_operation(void);
fsp_err_t vee_write_operation(uint32_t const rec_id, void *p_rec_data, uint32_t num_bytes);
fsp_err_t vee_read_operation(uint32_t const rec_id);
#endif
