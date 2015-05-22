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

    for (;;) {
        // digitalwrite 1
        //usleep(highus);
        // digitalwrite 0
        // usleep(lowus);
        sleep(1);
        if (pwmptr->pin == -1) {
            break;
        }
        cout << "pin: " << pwmptr->pin << ", high: " << pwmptr->highus << ", low:" << pwmptr->lowus << endl;
    }
}

pthread_t threads[18];
PWM pwms[18];
bool thread_exists[18];

void set_soft_pwm(int pin, int highus, int lowus) {
    PWM* pwm_ptr = &(pwms[pin]);
    pwm_ptr->pin = pin;
    pwm_ptr->highus = highus;
    pwm_ptr->lowus = lowus;

    pthread_t* thread_ptr = &(threads[pin]);
    if (!thread_exists[pin]) {
        if (0 != pthread_create(thread_ptr, NULL, set_soft_pwm, (void*) pwm_ptr)) {
            cout << "Fail to create pthread#" << pin << endl;
            return;
        }
        cout << "Success to create pthread#" << pin << endl;
        thread_exists[pin] = true;
    }
}

void unset_soft_pwm(int pin)
{
    cout << "Try to kill pthread#" << pin << endl;

    PWM* pwm_ptr = &(pwms[pin]);
    pwm_ptr->pin = -1;
    thread_exists[pin] = false;
}

int main() {
    cout << "stage 1" << endl;
    set_soft_pwm(1, 100, 200);
    set_soft_pwm(2, 100, 200);
    sleep(3);

    cout << "stage 2" << endl;
    set_soft_pwm(1, 200, 400);
    sleep(3);

    cout << "stage 3" << endl;
    unset_soft_pwm(1);
    sleep(3);

    cout << "stage 4" << endl;

    return 0;
}
