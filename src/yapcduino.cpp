#include <unistd.h>
#include "./yapcduino.h"
#include <nan.h>

using namespace v8;

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


/***********************************
 *
 * Soft PWM
 *
 **********************************/

// void set_soft_pwm(int pin, int highus, int lowus, int loops_to_live);
NAN_METHOD(setSoftPWM) {
    NanScope();
    set_soft_pwm(args[0]->NumberValue(),
                 args[1]->NumberValue(),
                 args[2]->NumberValue(),
                 args[3]->NumberValue());
    NanReturnUndefined();
}

// void set_soft_pwm_sync(int pin, int highus, int lowus, int loops_to_live);
NAN_METHOD(setSoftPWMSync) {
    NanScope();
    set_soft_pwm_sync(args[0]->NumberValue(),
                      args[1]->NumberValue(),
                      args[2]->NumberValue(),
                      args[3]->NumberValue());
    NanReturnUndefined();
}

// void unset_soft_pwm(int pin);
NAN_METHOD(unsetSoftPWM) {
    NanScope();
    unset_soft_pwm(args[0]->NumberValue());
    NanReturnUndefined();
}

// int get_soft_pwm_loop_count(int pin, int original_loops_to_live);
NAN_METHOD(getSoftPWMLoopCount) {
    NanScope();
    int ret = get_soft_pwm_loop_count(args[0]->NumberValue(),
                                      args[1]->NumberValue());
    NanReturnValue(NanNew<Number>(ret));
}

/***********************************
 *
 * INIT
 *
 **********************************/


void yapcduino_Init(Handle<Object> exports) {
    // important! init is defined in wiring.c
    // must be called before using pins
    init();

    exports->Set(NanNew<String>("pinMode"),
                 NanNew<FunctionTemplate>(pinMode)->GetFunction());

    exports->Set(NanNew<String>("digitalWrite"),
                 NanNew<FunctionTemplate>(digitalWrite)->GetFunction());

    exports->Set(NanNew<String>("digitalRead"),
                 NanNew<FunctionTemplate>(digitalRead)->GetFunction());

    exports->Set(NanNew<String>("analogWrite"),
                 NanNew<FunctionTemplate>(analogWrite)->GetFunction());

    exports->Set(NanNew<String>("analogReference"),
                 NanNew<FunctionTemplate>(analogReference)->GetFunction());

    exports->Set(NanNew<String>("pwmfreq_set"),
                 NanNew<FunctionTemplate>(pwmfreq_set)->GetFunction());

    exports->Set(NanNew<String>("millis"),
                 NanNew<FunctionTemplate>(millis)->GetFunction());

    exports->Set(NanNew<String>("micros"),
                 NanNew<FunctionTemplate>(micros)->GetFunction());

    exports->Set(NanNew<String>("delay"),
                 NanNew<FunctionTemplate>(delay)->GetFunction());

    exports->Set(NanNew<String>("delayMicroseconds"),
                 NanNew<FunctionTemplate>(delayMicroseconds)->GetFunction());

    exports->Set(NanNew<String>("delaySched"),
                 NanNew<FunctionTemplate>(delaySched)->GetFunction());

    exports->Set(NanNew<String>("delayMicrosecondsSched"),
                 NanNew<FunctionTemplate>(delayMicrosecondsSched)->GetFunction());

    exports->Set(NanNew<String>("pulseIn"),
                 NanNew<FunctionTemplate>(pulseIn)->GetFunction());

    exports->Set(NanNew<String>("shiftOut"),
                 NanNew<FunctionTemplate>(shiftOut)->GetFunction());

    exports->Set(NanNew<String>("shiftIn"),
                 NanNew<FunctionTemplate>(shiftIn)->GetFunction());

    exports->Set(NanNew<String>("setSoftPWM"),
                 NanNew<FunctionTemplate>(setSoftPWM)->GetFunction());

    exports->Set(NanNew<String>("setSoftPWMSync"),
                 NanNew<FunctionTemplate>(setSoftPWMSync)->GetFunction());

    exports->Set(NanNew<String>("unsetSoftPWM"),
                 NanNew<FunctionTemplate>(unsetSoftPWM)->GetFunction());

    exports->Set(NanNew<String>("getSoftPWMLoopCount"),
                 NanNew<FunctionTemplate>(getSoftPWMLoopCount)->GetFunction());
}

NODE_MODULE(yapcduino, yapcduino_Init)
