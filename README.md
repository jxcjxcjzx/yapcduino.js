# yapcduino.js

Yet another nodejs library for pcduino (extends jheising's node.pcduino but provide simple API and some extra function)

## Install

```bash
npm install yapcduino --save
```

## API

```javascript
var p = require('yapcduino');
p.PIN_COUNT // GPIO pin count
p.pinMode(10, p.INPUT); // Set pin #10 to input
p.pinMode(10, p.INPUT_PU); // Set pin #10 to input with pull-up
p.setPulse(pin, pulse, period, loops); // pulse and period are in us
```

## Source

The src/arduino comes from https://github.com/pcduino/c_environment

## Usage

### Use digital pin as your PWM pin?

Sometimes there are not enough PWM pin, or the target frequency is not available.
You can use digital signal to do that.
You can use my pcduino.digitalPWM function to do that. It will fork Node.js process and run loops there to make the PWM keep outputing. To stop, simply call pcduino.digitalPWM(pin, 0)
You can use digitalPulse to do it once. Or use startDigitalPulse


