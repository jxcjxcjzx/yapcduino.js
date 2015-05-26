#include <node.h>
#include "./arduino/Arduino.h"
#include <unistd.h>
#include "./softpwm.h"
#include <nan.h>

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;

// void pinMode(uint8_t, uint8_t);
NAN_METHOD(pinMode) {
    NanScope();
    pinMode(args[0]->NumberValue(), args[1]->NumberValue());
    NanReturnUndefined();
}

// void digitalWrite(uint8_t, uint8_t);
NAN_METHOD(digitalWrite) {
    NanScope();
    digitalWrite(args[0]->NumberValue(), args[1]->NumberValue());
    NanReturnUndefined();
}

// int digitalRead(uint8_t);
NAN_METHOD(digitalRead) {
    NanScope();
    int ret = digitalRead(args[0]->NumberValue());
    NanReturnValue(NanNew<Number>(ret));
}

// int analogRead(uint8_t);
NAN_METHOD(analogReference) {
    NanScope();
    int ret = analogRead(args[0]->NumberValue());
    NanReturnValue(NanNew<Number>(ret));
}

// void analogWrite(uint8_t, int);
NAN_METHOD(analogWrite) {
    NanScope();
    analogWrite(args[0]->NumberValue(), args[1]->NumberValue());
    NanReturnUndefined();
}


// void analogReference(uint8_t mode);
NAN_METHOD(analogReference) {
    NanScope();
    analogReference(args[0]->NumberValue());
    NanReturnUndefined();
}

// int pwmfreq_set(uint8_t pin, unsigned int freq);
NAN_METHOD(pwmfreq_set) {
    NanScope();
    int ret = pwmfreq_set(args[0]->NumberValue(), args[1]->NumberValue());
    NanReturnValue(NanNew<Number>(ret));
}

// unsigned long millis(void);
NAN_METHOD(millis) {
    NanScope();
    NanReturnValue(NanNew<Number>(millis()));
}

// unsigned long micros(void);
NAN_METHOD(micros) {
    NanScope();
    NanReturnValue(NanNew<Number>(micros()));
}

// void delay(unsigned long);
NAN_METHOD(delay) {
    NanScope();
    delay(args[0]->NumberValue());
    NanReturnUndefined();
}

// void delayMicroseconds(unsigned int us);
NAN_METHOD(delayMicroseconds) {
    NanScope();
    delay(args[0]->NumberValue());
    NanReturnUndefined();
}

// void delaySched(unsigned long);
NAN_METHOD(delaySched) {
    NanScope();
    delaySched(args[0]->NumberValue());
    NanReturnUndefined();
}

// void delayMicrosecondsSched(unsigned int us);
NAN_METHOD(delayMicrosecondsSched) {
    NanScope();
    delayMicrosecondsSched(args[0]->NumberValue());
    NanReturnUndefined();
}

// unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
// http://www.arduino.cc/en/Tutorial/Ping
// http://www.arduino.cc/en/Reference/PulseIn
NAN_METHOD(pulseIn) {
    NanScope();
    unsigned long ret = pulseIn(args[0]->NumberValue(),
                                args[1]->NumberValue(),
                                args[2]->NumberValue());
    NanReturnValue(NanNew<Number>(ret));
}

// void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
NAN_METHOD(shiftOut) {
    NanScope();
    shiftOut(args[0]->NumberValue(),
             args[1]->NumberValue(),
             args[2]->NumberValue(),
             args[3]->NumberValue());
    NanReturnUndefined();
}

// uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
NAN_METHOD(shiftIn) {
    NanScope();
    uint8_t ret = shiftIn(args[0]->NumberValue(),
                          args[1]->NumberValue(),
                          args[2]->NumberValue());
    NanReturnUndefined();
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
static void setSoftPWMSync(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
#else
Handle<Value> setSoftPWMSync(const Arguments& args) {
    HandleScope scope(isolate);
#endif
    int pin = args[0]->NumberValue();
    int highus = args[1]->NumberValue();
    int lowus = args[2]->NumberValue();
    int loops_to_live = args[3]->NumberValue();

    set_soft_pwm_sync(pin, highus, lowus, loops_to_live);

#ifndef __NODE_V0_11__
    return scope.Close(Undefined());
#endif
}

#ifdef __NODE_V0_11__
static void getSoftPWMLoopCount(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
#else
Handle<Value> getSoftPWMLoopCount(const Arguments& args) {
    HandleScope scope(isolate);
#endif
    int pin = args[0]->NumberValue();
    int original_loops_to_live = args[1]->NumberValue();

    int count = get_soft_pwm_loop_count(pin, original_loops_to_live);

#ifdef __NODE_V0_11__
    Local<Number> num = Number::New(isolate, count);
    args.GetReturnValue().Set(num);
#else
    Local<Number> num = Number::New(count);
    return scope.Close(num);
#endif
}

#ifdef __NODE_V0_11__
static void unsetSoftPWM(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
#else
Handle<Value> unsetSoftPWM(const Arguments& args) {
    HandleScope scope(isolate);
#endif

    int pin = args[0]->NumberValue();

    unset_soft_pwm(pin);

#ifndef __NODE_V0_11__
    return scope.Close(Undefined());
#endif
}

void yapcduino_Init(Local<Object> exports)
{

    // important! init is defined in wiring.c
    // must be called before using pins
    init();


}

NODE_MODULE(yapcduino, yapcduino_Init)
