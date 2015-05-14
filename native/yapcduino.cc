#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <Arduino.h>

using namespace v8;

Handle<Value> setPluse(const Arguments& args) {
    HandleScope scope;

    int pin = args[0]->NumberValue();
    int pluse = args[1]->NumberValue(); // pluse in us
    int period = args[2]->NumberValue(); // period in us
    int loops = args[3]->NumberValue(); // loop how many times

    for (int i = 0; i < loops; i++) {
        digitalWrite(pin, HIGH);
        delayMicroseconds(pluse);
        digitalWrite(pin, LOW);
        delayMicroseconds(period - pluse);
    }

    return scope.Close(Undefined());
}

void Init(Handle<Object> exports)
{
    init();

    exports->Set(v8::String::NewSymbol("setPluse"),
                 FunctionTemplate::New(setPluse)->GetFunction());
}

NODE_MODULE(node_pcduino_helper, Init)
