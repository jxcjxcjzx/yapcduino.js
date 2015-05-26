#include "./arduino/Arduino.h"
#include "./softpwm.c"
#include <node.h>
#include <cbind_yapcduino.h>

void init(v8::Handle<v8::Object> exports) {
    init(); // important! init is defined in wiring.c
    cbind::init_yapcduino(exports);
}

NODE_MODULE(yapcduino, init);
