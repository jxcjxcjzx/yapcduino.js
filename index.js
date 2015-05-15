var pcduino = require('pcduino');

// load digital API
var API = Object.create(pcduino.digital);

// load analog API
API.analogWrite = pcduino.digital.analogWrite;
API.analogRead = pcduino.digital.analogRead;

// load extra native API
var ExtraNative = require('./build/Release/yapcduino');

/**
 * Use DigitalWrite to Output a Pulse once
 * This is sync version using usleep, use startDigitalPulse if you want it run forever
 *
 * @param {Int} pin - Pin ID
 * @param {Int} pulse - Pulse in us
 * @param {Int} period - Period in us, defaults to 20 * 1000
 * @param {Int} loops - Loop how many times, defaults to 1
 */
API.digitalPulse = function(pin, pulse, period, loops) {
    if (typeof period === "undefined") {
        period = 20 * 1000;
    }
    if (typeof loops === "undefined") {
        loops = 1;
    }
    ExtraNative.digitalPulse(pin, pulse, period, loops);
};

API.digitalPWM = require('./lib/digital-pwm');

/**
 * pulseIn
 *
 * @param {Int} pin - Pin ID
 * @param {Int} value - Type of pulse to read: either pcduino.HIGH or pcduino.LOW (int)
 * @param {Int} timeout - The number of microseconds to wait for the pulse to start; default is one second
 */
API.pulseIn = function(pin, value, timeout) {
    if (typeof timeout === "undefined") {
        timeout = 1000 * 1000; // 1s
    }
    ExtraNative.pulseIn(pin, value, timeout);
};


module.exports = API;
