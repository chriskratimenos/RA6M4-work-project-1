#ifndef VEE_FLASH_H_
#define VEE_FLASH_H_

void vee_flash_init(void);
void vee_format_operation(void);
void vee_write_operation(uint32_t const rec_id, void *p_rec_data, uint32_t num_bytes);
void vee_read_operation(uint32_t const rec_id, void *p_read_buffer, uint32_t num_bytes);
#endif
