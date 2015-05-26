#include <node.h>
#include <node_version.h>
#include <uv.h>
#include "./arduino/Arduino.h"
#include <unistd.h>
#include <pthread.h>
#include "./softpwm.h"
#include "common.h"

using namespace v8;
using namespace node;

// http://www.arduino.cc/en/Tutorial/Ping
// http://www.arduino.cc/en/Reference/PulseIn
#ifdef __NODE_V0_11__
static void pulseIn(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
#else
Handle<Value> pulseIn(const Arguments& args) {
    HandleScope scope;
#endif
    int pin = args[0]->NumberValue();
    int value = args[1]->NumberValue(); // type of pulse to read: either HIGH or LOW (int)
    int timeout = args[2]->NumberValue();

    int us = pulseIn(pin, value, timeout); // the length of the pulse in us

#ifdef __NODE_V0_11__
    Local<Number> num = Number::New(isolate, us);
    args.GetReturnValue().Set(num);
#else
    Local<Number> num = Number::New(us);
    return scope.Close(num);
#endif
}

#ifdef __NODE_V0_11__
static void usleep(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
#else
Handle<Value> usleep(const Arguments& args) {
    HandleScope scope;
#endif
    int us = args[0]->NumberValue();
    usleep(us);

#ifndef __NODE_V0_11__
    return scope.Close(Undefined());
#endif
}

#ifdef __NODE_V0_11__
static void setSoftPWM(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
#else
Handle<Value> setSoftPWM(const Arguments& args) {
    HandleScope scope(isolate);
#endif
    int pin = args[0]->NumberValue();
    int highus = args[1]->NumberValue();
    int lowus = args[2]->NumberValue();
    int loops_to_live = args[3]->NumberValue();

    set_soft_pwm(pin, highus, lowus, loops_to_live);

#ifndef __NODE_V0_11__
    return scope.Close(Undefined());
#endif
}

#ifdef __NODE_V0_11__
static void setSoftPWM(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
Handle<Value> setSoftPWMSync(const Arguments& args) {
    HandleScope scope(isolate);

    int pin = args[0]->NumberValue();
    int highus = args[1]->NumberValue();
    int lowus = args[2]->NumberValue();
    int loops_to_live = args[3]->NumberValue();

    set_soft_pwm_sync(pin, highus, lowus, loops_to_live);

    return scope.Close(Undefined());
}

Handle<Value> getSoftPWMLoopCount(const Arguments& args) {
    HandleScope scope(isolate);

    int pin = args[0]->NumberValue();
    int original_loops_to_live = args[1]->NumberValue();

    int count = get_soft_pwm_loop_count(pin, original_loops_to_live);

    Local<Number> num = Number::New(count);
    return scope.Close(num);
}

Handle<Value> unsetSoftPWM(const Arguments& args) {
    HandleScope scope(isolate);

    int pin = args[0]->NumberValue();

    unset_soft_pwm(pin);

    return scope.Close(Undefined());
}

void Init(Handle<Object> exports)
{

    init(); // important! init is defined in wiring.c

    exports->Set(v8::String::NewSymbol("pulseIn"),
                 FunctionTemplate::New(pulseIn)->GetFunction());

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
