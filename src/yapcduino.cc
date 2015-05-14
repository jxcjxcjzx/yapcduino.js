#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "./arduino/Arduino.h"

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

Handle<Value> setPulse(const Arguments& args) {
    HandleScope scope;

    int pin = args[0]->NumberValue();
    int pulse = args[1]->NumberValue(); // pulse in us
    int period = args[2]->NumberValue(); // period in us
    int loops = args[3]->NumberValue(); // loop how many times

    for (int i = 0; i < loops; i++) {
        digitalWrite(pin, HIGH);
        delayMicroseconds(pulse);
        digitalWrite(pin, LOW);
        delayMicroseconds(period - pulse);
    }

    return scope.Close(Undefined());
}

void Init(Handle<Object> exports)
{
    init();

    exports->Set(v8::String::NewSymbol("setPulse"),
                 FunctionTemplate::New(setPulse)->GetFunction());
}

NODE_MODULE(node_pcduino_helper, Init)
