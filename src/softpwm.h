#ifdef _SOFTPWM_H_
#define _SOFTPWM_H_

void set_soft_pwm(int pin, int highus, int lowus, int loops_to_live);
void set_soft_pwm_sync(int pin, int highus, int lowus, int loops_to_live);
void unset_soft_pwm(int pin);
int get_soft_pwm_loops_count(int pin, int original_loops_to_live);

#endif
