#ifndef GPT_TIMER_H_
#define GPT_TIMER_H_
void init_gpt_timer(void);
void start_gpt_timer(void);
void stop_gpt_timer(void);
extern volatile bool g_timer_overflow;
#endif /* GPT_TIMER_H_ */
