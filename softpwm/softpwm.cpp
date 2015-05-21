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

void *fn(void* _pwm);

void *fn(void* _pwm)
{
    PWM* pwmptr = (PWM *) _pwm;
    PWM pwm;
    int pin, highus, lowus;

    for (;;) {
        pwm = *pwmptr;
        pin = pwm.pin;
        highus = pwm.highus;
        lowus = pwm.lowus;
        cout << pin << "," << highus << "," << lowus << endl;
    }
}

int main() {
    PWM pwm;
    pwm.highus = 100;
    pwm.lowus = 200;
    pwm.pin = 1;

    pthread_t thread1;
    pthread_create(&thread1,
                   NULL,
                   fn,
                   (void*) &pwm);
    usleep(100);
    pwm.highus = 200;
    pwm.lowus = 400;
    usleep(100);
    pthread_kill(thread1, 9);
    return 0;
}
