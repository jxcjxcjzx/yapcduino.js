#include <node.h>
#include <uv.h>
#include "./arduino/Arduino.h"
#include <unistd.h>
#include <pthread.h>
#include "./softpwm.h"

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

Handle<Value> setSoftPWM(const Arguments& args) {
    HandleScope scope;

    int pin = args[0]->NumberValue();
    int highus = args[1]->NumberValue();
    int lowus = args[2]->NumberValue();
    int loops_to_live = args[3]->NumberValue();

    set_soft_pwm(pin, highus, lowus, loops_to_live);

    return scope.Close(Undefined());
}

Handle<Value> setSoftPWMSync(const Arguments& args) {
    HandleScope scope;

    int pin = args[0]->NumberValue();
    int highus = args[1]->NumberValue();
    int lowus = args[2]->NumberValue();
    int loops_to_live = args[3]->NumberValue();

    set_soft_pwm_sync(pin, highus, lowus, loops_to_live);

    return scope.Close(Undefined());
}

Handle<Value> getSoftPWMLoopCount(const Arguments& args) {
    HandleScope scope;

    int pin = args[0]->NumberValue();
    int original_loops_to_live = args[1]->NumberValue();

    int count = get_soft_pwm_loops_count(pin, original_loops_to_live);

    Local<Number> num = Number::New(count);
    return scope.Close(num);
}

Handle<Value> unsetSoftPWM(const Arguments& args) {
    HandleScope scope;

    int pin = args[0]->NumberValue();

    unset_soft_pwm(pin);

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

    exports->Set(v8::String::NewSymbol("setSoftPWM"),
                 FunctionTemplate::New(setSoftPWM)->GetFunction());

    exports->Set(v8::String::NewSymbol("setSoftPWMSync"),
                 FunctionTemplate::New(setSoftPWMSync)->GetFunction());

    exports->Set(v8::String::NewSymbol("unsetSoftPWM"),
                 FunctionTemplate::New(unsetSoftPWM)->GetFunction());

    exports->Set(v8::String::NewSymbol("getSoftPWMLoopCount"),
                 FunctionTemplate::New(getSoftPWMLoopCount)->GetFunction());
}

NODE_MODULE(yapcduino, Init)
