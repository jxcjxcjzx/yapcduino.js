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

### Output

### (Sync) Delay

```javascript
p.delay(ms);
p.delayMicroseconds(us);
```

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
