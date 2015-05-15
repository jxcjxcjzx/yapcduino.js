var pcduino = require('pcduino');

// load digital API
var API = Object.create(pcduino.digital);

// load analog API
API.analogWrite = pcduino.digital.analogWrite;
API.analogRead = pcduino.digital.analogRead;

// load extra native API
var ExtraNative = require('./build/Release/yapcduino');

var digitalPulse = require('./lib/digital-pulse');

API.digitalPulse = digitalPulse.digitalPulse;

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
