#include <node.h>
#include <uv.h>
#include "./arduino/Arduino.h"
#include <unistd.h>

using namespace v8;

// http://www.arduino.cc/en/Tutorial/Ping
// http://www.arduino.cc/en/Reference/PulseIn
Handle<Value> pulseIn(const Arguments& args) {
    HandleScope scope;

    int pin = args[0]->NumberValue();
    int value = args[1]->NumberValue(); // type of pulse to read: either HIGH or LOW (int)
    int timeout = args[2]->NumberValue();

    int us = pulseIn(pin, value, timeout); // the length of the pulse in us

    Local<Number> num = Number::New(us);
    return scope.Close(num);
}

void digitalWritePWM(int pin, double dutyCycle, int period, int loops, bool keepLooping) {
    int sleeptime = dutyCycle * period;

    while (keepLooping || loops-- > 0) {
        digitalWrite(pin, HIGH);
        usleep(sleeptime);
        digitalWrite(pin, LOW);
        usleep(period - sleeptime);
    }
}

Handle<Value> digitalWritePWM(const Arguments& args) {
    HandleScope scope;

    int pin = args[0]->NumberValue();
    double dutyCycle = args[1]->NumberValue();
    int period = args[2]->NumberValue();
    int loops = args[3]->NumberValue();
    bool sync = args[4]->NumberValue() == 1;
    bool keepLooping = loops == -1;

    if (sync) {
        digitalWritePWM(pin, dutyCycle, period, loops, keepLooping);
    } else {
    }
}

Handle<Value> digitalPulse(const Arguments& args) {
    HandleScope scope;

    int pin = args[0]->NumberValue();
    int pulse = args[1]->NumberValue(); // pulse in us
    int period = args[2]->NumberValue(); // period in us
    int loops = args[3]->NumberValue(); // loop how many times

    for (int i = 0; i < loops; i++) {
        digitalWrite(pin, HIGH);
        usleep(pulse);
        digitalWrite(pin, LOW);
        usleep(period - pulse);
    }

    return scope.Close(Undefined());
}

Handle<Value> usleep(const Arguments& args) {
    HandleScope scope;

    int us = args[0]->NumberValue();
    usleep(us);

    return scope.Close(Undefined());
}

void Init(Handle<Object> exports)
{
    init(); // important! init is defined in wiring.c

    exports->Set(v8::String::NewSymbol("pulseIn"),
                 FunctionTemplate::New(pulseIn)->GetFunction());

    exports->Set(v8::String::NewSymbol("digitalPulse"),
                 FunctionTemplate::New(digitalPulse)->GetFunction());

    exports->Set(v8::String::NewSymbol("usleep"),
                 FunctionTemplate::New(usleep)->GetFunction());
}

NODE_MODULE(yapcduino, Init)
