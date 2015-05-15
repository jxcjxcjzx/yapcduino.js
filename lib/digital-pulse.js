var ExtraNative = require('../build/Release/yapcduino');
var child_process = require('child_process');

/**
 * Use DigitalWrite to Output a Pulse once
 * This is sync version using usleep, use startDigitalPulse if you want it run forever
 *
 * @param {Int} pin - Pin ID
 * @param {Int} pulse - Pulse in us
 * @param {Int} period - Period in us, defaults to 20 * 1000
 * @param {Int} loops - Loop how many times, defaults to 1
 */
var digitalPulse = function(pin, pulse, period, loops) {
    if (typeof period === "undefined") {
        period = 20 * 1000;
    }
    if (typeof loops === "undefined") {
        loops = 1;
    }
    ExtraNative.digitalPulse(pin, pulse, period, loops);
};

var processPool = {};

/**
 * Let the pin output the digital pulse forever (unless stopDigitalPulse called)
 * This function is async, it will open a new Node.js Process and the loop will run there.
 *
 * @param {Int} pin - Pin ID
 * @param {Int} pulse - Pulse in us
 * @param {Int} period - Period in us, default to 20 * 1000
 */
var startDigitalPulse = function(pin, pulse, period) {
    if (typeof period === "undefined") {
        period = 20 * 1000;
    }
    if (processPool[pin]) {
        stopDigitalPulse(pin);
    }
    processPool[pin] = child_process.fork('./digital-pulse-slave.js', [], {env: {
        pin: pin,
        pulse: pulse,
        period: period
    }});
};

/**
 * Let the pin stop
 *
 * @param {Int} pin - Pin ID
 * @param {Int} pulse - Pulse in us
 * @param {Int} period - Period in us, default to 20 * 1000
 */
var stopDigitalPulse = function(pin) {
};

module.exports = {
    digitalPulse: digitalPulse,
    startDigitalPulse: startDigitalPulse,
    stopDigitalPulse: stopDigitalPulse
};
