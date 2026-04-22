/*
 * gpt_timer.h
 *
 *  Created on: 20 Απρ 2026
 *      Author: a5163766
 */
#include "hal_data.h"

#ifndef GPT_TIMER_H_
#define GPT_TIMER_H_
void init_gpt_timer(void);
void start_gpt_timer(void);
void stop_gpt_timer(void);
extern volatile bool timer_overflow;
#endif /* GPT_TIMER_H_ */
