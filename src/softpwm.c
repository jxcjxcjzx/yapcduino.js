// Copyright (c) 2015 Zeno Zeng, licensed under LGPL
// Special thanks to Senorsen Zhang and Robert Zhang

#include "./softpwm.h"

#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "./arduino/Arduino.h"

pthread_t threads[18];
PWM pwms[18];
bool thread_exists[18];

struct PWM
{
    int highus;
    int lowus;
    int pin;
    int loops;
};

void *set_soft_pwm(void* _pwm)
{
    PWM* pwm_ptr = (PWM *) _pwm;

    for (;;) {
        if (pwmptr->pin == -1) {
            break;
        }

        digitalWrite(pin, HIGH);
        usleep(pwm_ptr->highus);
        digitalWrite(pin, LOW);
        usleep(pwm_ptr->lowus);
    }
}

// run soft pwm in thread#pin forever(loops = -1) or for n loops (async)
void set_soft_pwm(int pin, int highus, int lowus, int loops) {
    PWM* pwm_ptr = &(pwms[pin]);
    pwm_ptr->pin = pin;
    pwm_ptr->highus = highus;
    pwm_ptr->lowus = lowus;
    pwm_ptr->loops = loops;

    pthread_t* thread_ptr = &(threads[pin]);
    if (0 != pthread_create(thread_ptr, NULL, set_soft_pwm, (void*) pwm_ptr)) {
        return;
    }
    thread_exists[pin] = true;
}

// (sync version) wait till pthread exited
void unset_soft_pwm(int pin)
{
    PWM* pwm_ptr = &(pwms[pin]);

    // wait until pthread no longer running
    while (pthread_kill(threads[pin], 0) == 0)
    {
        pwm_ptr->pin = -1;
        usleep(10);
    }

    thread_exists[pin] = false;
}
