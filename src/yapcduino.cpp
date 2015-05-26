#include <node.h>
#include "./yapcduino.h"

#include <cbind_yapcduino.h>

void init(v8::Handle<v8::Object> exports) {
    cbind::init_yapcduino(exports);
}

NODE_MODULE(yapcduino, init);
