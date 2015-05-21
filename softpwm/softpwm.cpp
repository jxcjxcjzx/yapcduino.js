#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

void *fn(void* _highus);

void *fn(void* _highus)
{
    for (;;) {
        int *highus;
        // int *lowus;
        highus = (int *) _highus;
        // lowus = (int *) _lowus;
        // cout << highus << "," << lowus << endl;
        cout << *highus << endl;
    }
}

int main() {
    cout << "init softpwm" << endl;
    pthread_t thread1;
    int highus = 100;
    int lowus = 10;
    pthread_create(&thread1,
                   NULL,
                   fn,
                   (void*) &highus);
    usleep(100);
    highus = 200;
    lowus = 20;
    usleep(100);
    pthread_kill(thread1, 9);
    return 0;
}
