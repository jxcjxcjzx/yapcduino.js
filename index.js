var pcduino = require('pcduino');

// load digital API
var API = Object.create(pcduino.digital);

// load analog API
API.analogWrite = pcduino.digital.analogWrite;
API.analogRead = pcduino.digital.analogRead;

// load extra native API
var ExtraNative = require('./../build/Release/yapcduino');

/**
 * Set Pulse
 *
 * @param {Int} pin - Pin number
 * @param {Int} pulse - Pluse in us
 * @param {Int} period - Period in us, defaults to 20 * 1000
 * @param {Int} loops - Loop how many times, defaults to 1
 */
var setPulse = function(pin, pulse, period, loops) {
    if (typeof period === "undefined") {
        period = 20;
    }
    if (typeof loops === "undefined") {
        loops = 1;
    }
    ExtraNative.setPulse(pin, pulse, period, loops);
};


module.exports = API;
