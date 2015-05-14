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
```
