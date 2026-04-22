#ifndef ADC_H_
#define ADC_H_

void adc_init(void);
void adc_calibrate(void);
int16_t adc_scan_read(void);
#endif /* ADC_H_ */
