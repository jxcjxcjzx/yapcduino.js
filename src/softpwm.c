// Copyright (c) 2015 Zeno Zeng, licensed under LGPL
// Special thanks to Senorsen Zhang and Robert Zhang

#include "./softpwm.h"

#include "./arduino/Arduino.h"

#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>

struct PWM
{
    int highus;
    int lowus;
    int pin;
    int loops_to_live;
};

typedef struct PWM PWM;

pthread_t threads[18];
PWM pwms[18];
bool thread_exists[18];

void *set_soft_pwm_for_n_loops(void* _pwm)
{
    PWM* pwm_ptr = (PWM *) _pwm;

    while (pwm_ptr->loops_to_live-- > 0) {
        digitalWrite(pwm_ptr->pin, HIGH);
        usleep(pwm_ptr->highus);
        digitalWrite(pwm_ptr->pin, LOW);
        usleep(pwm_ptr->lowus);
    }
}

// get how many loops of the pin since last set
// use get_loops_lived(pin, -1) if original is run forever
int get_soft_pwm_loop_count(int pin, int original_loops_to_live) {
    original_loops_to_live = original_loops_to_live < 0 ? 2147483647 : original_loops_to_live;
    PWM* pwm_ptr = &(pwms[pin]);
    return (original_loops_to_live - pwm_ptr->loops_to_live);
}

// run soft pwm in thread#pin forever(loops = -1) or for n loops (async)
// note that max loops_to_live is 2147483647
// count can be calculated based on orginal loops_to_live and current loops_to_live
void set_soft_pwm(int pin, int highus, int lowus, int loops_to_live) {
    PWM* pwm_ptr = &(pwms[pin]);
    pwm_ptr->pin = pin;
    pwm_ptr->highus = highus;
    pwm_ptr->lowus = lowus;
    pwm_ptr->loops_to_live = loops_to_live < 0 ? 2147483647 : loops_to_live;

    if (thread_exists[pin]) {
        return;
    }
    pthread_t* thread_ptr = &(threads[pin]);
    if (0 != pthread_create(thread_ptr, NULL, set_soft_pwm_for_n_loops, (void*) pwm_ptr)) {
        return; // error occurs
    }
    thread_exists[pin] = true;
}

void set_soft_pwm_sync(int pin, int highus, int lowus, int loops_to_live) {
    set_soft_pwm(pin, highus, lowus, loops_to_live);
    void **retval;
    pthread_join(threads[pin], retval);
}

// (sync version) wait till pthread exited
void unset_soft_pwm(int pin)
{
    PWM* pwm_ptr = &(pwms[pin]);

    // wait until pthread no longer running
    while (pthread_kill(threads[pin], 0) == 0)
    {
        pwm_ptr->loops_to_live = 0;
        usleep(10);
    }

    thread_exists[pin] = false;
}
