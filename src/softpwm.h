#ifdef _SOFTPWM_H_
#define _SOFTPWM_H_

void set_soft_pwm(int pin, int highus, int lowus);
void unset_soft_pwm(int pin);

#endif
