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
p.pinMode(10, p.INPUT); // Set pin #10 to input
p.pinMode(10, p.INPUT_PULLUP); // Set pin #10 to input with pull-up
var ret = p.digitalRead(10);
```

```javascript
p.pinMode(0, p.OUTPUT);
p.digitalWrite(0, p.HIGH);
p.digitalWrite(0, p.LOW);
```

```javascript
// Note: only 3, 5, 6, 9, 10, and 11 are PWM pins
p.analogWrite(3, 16);
var ret = p.analogRead(3);
```

### Global Mode

Sometimes it's silly to write all this functions with a prefix.
Since yapcduino@0.9.0, we have introduced global mode.

```javascript
require('yapcduino')({global: true});
pinMode(0, OUTPUT);
digitalWrite(0, HIGH);
```

### Arduino Binding

The following functions are provided using Node.js's Nan binding.
And can be called like `pcduino.pinMode(0, pcduino.OUTPUT)`

```c
void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int digitalRead(uint8_t);
int analogRead(uint8_t);
/*
 * only pin (3/5/6/9/10/11) can be used as analog
 */
void analogReference(uint8_t mode);
void analogWrite(uint8_t, int);
/*
 * pin(3/9/10/11) support frequency[125-2000]Hz @different dutycycle
 * pin(5/6) support frequency[195,260,390,520,781] @256 dutycycle
 */
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

### Servo

```javascript
require('yapcduino')({global: true});
var s = new Servo(3, {type: 'SG90'}); // available types: ['SG90']
for(var i = 1; i <= 180; i += 5) {
    Native.delay(100);
    console.log(i);
    s.write(i);
}
s.stop();
```

#### jsdoc

```javascript
/**
 * Construct a Servo object
 *
 * @param {Int} pin - pwm pin to use (only 3, 5, 6, 9, 10, and 11)
 * @param {Object} options - Options for servo
 * @param {String} options.type - Type of your servo, available types: ['SG90']
 * @param {Int} options.frequency - Frequency
 */
function Servo(pin, options) {}

/**
 * Set angle to given angle
 *
 * @param {Int} angle - Angle in degree
 */
Servo.prototype.write = function(angle) {}

/**
 * Return current angle
 */
Servo.prototype.read = function() {}

/**
 * Stop Servo
 */
Servo.prototype.stop = function() {}
```

### SoftPWM (Powered by pthread)

Use your GPIO pin to fake PWM pin using CPU.

**Improtant**: SoftPWM may not be stable enough for your **servo**, which expects a pulse over a very tight range. Use SoftPWM in servo may cause positions jumps.

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

#### jsdoc

```javascript
function SoftPWM(pin) {}

/**
 * Attach the SoftPWM instance to a new pin
 *
 */
SoftPWM.prototype.attach = function(pin) {}

/**
 * Detach the SoftPWM instance from original pin (will unset output of original pin and set this.pin to null)
 *
 */
SoftPWM.prototype.detach = function() {}

/**
 * Get count of loops of the pin since last write
 *
 */
SoftPWM.prototype.getLoopCount = function() {}

/**
 * Writes a PWM wave to a p in (using digitalWrite).
 * To stop, simply call pwm.detach();
 *
 * @see http://www.arduino.cc/en/Tutorial/PWM
 * @see http://www.arduino.cc/en/Reference/analogWrite
 * @param {Float} dutyCycle - Duty Cycle [0, 1]
 * @param {Object} options - Options for PWM
 * @param {Int} options.period - Period (in us), defaults to 20 * 1000
 * @param {Int} options.frequency - Frequency, period will be ignored if frequency set
 * @param {Number} options.loops - (loops to live) How many loops should it run, defaults to Infinity (actually is 2147483647), note that -1 will be converted to 2147483647
 * @param {Bool} options.sync - Whether to run it in sync mode, defaults to false
 */
SoftPWM.prototype.write = function(dutyCycle, options) {}

/**
 * Read last set dutyCycle (will return undefined if not set)
 *
 */
SoftPWM.prototype.read = function() {}
```

## Source

The src/arduino comes from https://github.com/pcduino/c_environment

## Authors

- Zeno Zeng \<zenoofzeng@gmail.com\>

- Senorsen \<sen@senorsen.com\>

## Changelog

### v0.10.0

- Add Servo API

### v0.9.3

- Fix symbol lookup error (fix missing src: wiring\_shift.c, wiring\_analog.c)

### v0.9.2

- Fix delayMicroseconds

    typo: delay -> delayMicroseconds

### v0.9.0

- Option for Global Mode

    ```javascript
    require('yapcduino')({global: true});
    pinMode(0, OUTPUT);
    digitalWrite(0, HIGH);
    ```

### v0.8.1

- Fix constant reference

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

- No longer requires node-pcduino now

## Links

- [How can I kill a particular thread of a process?](http://unix.stackexchange.com/questions/1066/how-can-i-kill-a-particular-thread-of-a-process)
