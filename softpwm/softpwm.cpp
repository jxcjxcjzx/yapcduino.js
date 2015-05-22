// Copyright (c) 2015 Zeno Zeng, licensed under LGPL
// Special thanks to Senorsen Zhang

#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

struct PWM
{
    int highus;
    int lowus;
    int pin;
};

void *set_soft_pwm(void* _pwm)
{
    PWM* pwmptr = (PWM *) _pwm;
    PWM pwm;
    int pin, highus, lowus;

    for (;;) {
        pwm = *pwmptr;
        pin = pwm.pin;
        highus = pwm.highus;
        lowus = pwm.lowus;
        // digitalwrite 1
        //usleep(highus);
        // digitalwrite 0
        // usleep(lowus);
        cout << endl;
        cout << "pin: " << pin << ", high: " << highus << ", low:" << lowus << endl;
    }
}

pthread_t threads[18];
PWM pwms[18];

void set_soft_pwm(int pin, int highus, int lowus) {
    PWM* pwm_ptr = &(pwms[pin]);
    (*pwm_ptr).pin = pin;
    (*pwm_ptr).highus = highus;
    (*pwm_ptr).lowus = lowus;

    pthread_t* thread_ptr = &(threads[pin]);
    pthread_create(thread_ptr,
                   NULL,
                   set_soft_pwm,
                   (void*) pwm_ptr);
}

void unset_soft_pwm(int pin) {
    pthread_kill(threads[pin], 9);
}

int main() {
    set_soft_pwm(1, 100, 200);
    usleep(200);

    // set_soft_pwm(2, 100, 200);
    set_soft_pwm(1, 200, 400);
    usleep(200);

    // set_soft_pwm(1, 200, 400);
    // set_soft_pwm(2, 200, 400);
    unset_soft_pwm(1);

    return 0;
}
