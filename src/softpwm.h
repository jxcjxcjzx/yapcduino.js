#ifndef _SOFTPWM_H_
#define _SOFTPWM_H_

#ifdef __cplusplus
extern "C"{
#endif

void set_soft_pwm(int pin, int highus, int lowus, int loops_to_live);
void set_soft_pwm_sync(int pin, int highus, int lowus, int loops_to_live);
void unset_soft_pwm(int pin);
int get_soft_pwm_loop_count(int pin, int original_loops_to_live);
void sync_wait_pin(int pin);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
