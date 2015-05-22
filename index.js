var pcduino = require('pcduino');

var API = {};

// load digital API
Object.keys(pcduino.digital).forEach(function(method) {
    API[method] = pcduino.digital[method];
});

// load analog API
API.analogWrite = pcduino.analog.analogWrite;
API.analogRead = pcduino.analog.analogRead;

// load extra native API
var Native = require('./build/Release/yapcduino');

/**
 * Suspend execution for given microseconds
 *
 * @param {Int} us - time for suspending
 */
API.usleep = Native.usleep;

/**
 * Suspend execution for given microseconds
 *
 * @param {Int} us - time for suspending
 */
API.delayMicroseconds = Native.usleep;

/**
 * Suspend execution for given miliseconds
 *
 * @param {Int} ms - time for suspending
 */
API.delay = function(ms) {
    API.delayMicroseconds(ms * 1000);
};

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
    Native.pulseIn(pin, value, timeout);
};


module.exports = API;
