# yapcduino.js

Yet another nodejs library for pcduino (extends jheising's node.pcduino but provide simple API and some extra function)

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

### SoftPWM (Powered by pthread)

Use your GPIO pin to fake PWM pin using CPU.

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

## Usage

### Use digital pin as your PWM pin?

Sometimes there are not enough PWM pin, or the target frequency is not available.
You can use digital signal to do that.
You can use my pcduino.digitalPWM function to do that. It will fork Node.js process and run loops there to make the PWM keep outputing. To stop, simply call pcduino.digitalPWM(pin, 0)
You can use digitalPulse to do it once. Or use startDigitalPulse

## Links

- [How can I kill a particular thread of a process?](http://unix.stackexchange.com/questions/1066/how-can-i-kill-a-particular-thread-of-a-process)
