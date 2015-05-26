# yapcduino.js

Yet another nodejs library for pcduino built for modern nodejs and provide more arduino functions and wrapper.

Yapcduino should work in Node.js 0.10 and 0.12 as well as io.js.

## Install

```bash
npm install yapcduino --save
```

## Usage

### Basic Features

```javascript
var p = require('yapcduino');
p.PIN_COUNT // GPIO pin count
p.pinMode(10, p.INPUT); // Set pin #10 to input
p.pinMode(10, p.INPUT_PU); // Set pin #10 to input with pull-up
var ret = p.digitalRead(10);
```

```javascript
p.pinMode(0, p.OUTPUT);
p.digitalWrite(0, 1);
p.digitalWrite(0, 0);
``

```javascript
// Note: only 3, 5, 6, 9, 10, and 11 are PWM pins
p.analogWrite(3, 16);
var ret = p.analogRead(3);
```

### (Sync) Delay

```javascript
p.delay(ms);
p.delayMicroseconds(us);
```

### Arduino Binding

The following functions are provided using Node.js's Nan binding.
And can be called like `pcduino.pinMode(0, pcduino.OUTPUT)`

```c
void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int digitalRead(uint8_t);
int analogRead(uint8_t);
void analogReference(uint8_t mode);
void analogWrite(uint8_t, int);
int pwmfreq_set(uint8_t pin, unsigned int freq);
unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long);
void delayMicroseconds(unsigned int us);
void delaySched(unsigned long);
void delayMicrosecondsSched(unsigned int us);
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
```

### Constants

```
HIGH: 0x1,
LOW: 0x0,

INPUT: 0x0,
OUTPUT: 0x1,
INPUT_PULLUP: 0x2,

LSBFIRST: 0,
MSBFIRST: 1,

CHANGE: 1,
FALLING: 2,
RISING: 3
```

### SoftPWM (Powered by pthread)

Use your GPIO pin to fake PWM pin using CPU.
Improtant: SoftPWM may not be stable enough for your servo, which expects a pulse over a very tight range. Use SoftPWM in servo may cause positions jumps.

```javascript
var pin = 0;
var pwm = new SoftPWM(pin);
var dutyCycle = 0.5;
pwm.write(dutyCycle, {frequency: 980, loops: Infinity}); // run the PWM forever
// everything done? stop and unset this.pin
// Note: after detach, you have to attach(pin) before call write or read
pwm.detach();
```

```javascript
var pin = 0;
var pwm = new SoftPWM(pin);
var dutyCycle = 0.5;
var us = 20 * 1000; // 500HZ
pwm.write(dutyCycle, {period: us, loops: 1000});
// Get count of loops of the pin since last write (useful for stepping motor)
var count = pwm.getLoopCount();
```

See the detail jsdoc in: https://github.com/zenozeng/yapcduino.js/blob/master/lib/softpwm.js

## Source

The src/arduino comes from https://github.com/pcduino/c_environment

## Authors

- Zeno Zeng \<zenoofzeng@gmail.com\>

- Senorsen \<sen@senorsen.com\>

## Changelog

### v0.8.0

- Using nan to rewrite bindings, now should work in Node.js 0.10 and 0.12 as well as io.js.

- Add more bindings (now the following are supported)

    ```c
    void pinMode(uint8_t, uint8_t);
    void digitalWrite(uint8_t, uint8_t);
    int digitalRead(uint8_t);
    int analogRead(uint8_t);
    void analogReference(uint8_t mode);
    void analogWrite(uint8_t, int);
    int pwmfreq_set(uint8_t pin, unsigned int freq);
    unsigned long millis(void);
    unsigned long micros(void);
    void delay(unsigned long);
    void delayMicroseconds(unsigned int us);
    void delaySched(unsigned long);
    void delayMicrosecondsSched(unsigned int us);
    unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
    void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
    uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
    ```

- Add constants (now the following are supported)

```javascript
module.exports = {
    HIGH: 0x1,
    LOW: 0x0,

    INPUT: 0x0,
    OUTPUT: 0x1,
    INPUT_PULLUP: 0x2,

    LSBFIRST: 0,
    MSBFIRST: 1,

    CHANGE: 1,
    FALLING: 2,
    RISING: 3
};
```

- No longer requires node-pcduino now

## Links

- [How can I kill a particular thread of a process?](http://unix.stackexchange.com/questions/1066/how-can-i-kill-a-particular-thread-of-a-process)
