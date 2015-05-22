var Native = require('./build/Release/yapcduino');

/**
 * Writes a PWM wave to a pin (using digitalWrite).
 * To stop, simply call pcduino.digitalWritePWM(pin, {loops: 0})
 *
 * @see http://www.arduino.cc/en/Tutorial/PWM
 * @see http://www.arduino.cc/en/Reference/analogWrite
 * @param {Int} pin - Pin ID
 * @param {Float} dutyCycle - Duty Cycle [0, 1]
 * @param {Object} options - Options for PWM
 * @param {Int} options.period - Period (in us), defaults to 20 * 1000
 * @param {Int} options.frequency - Frequency, period will be ignored if frequency set
 * @param {Number} options.loops - (loops to live) How many loops should it run, defaults to Infinity (actually is 2147483647), note that -1 will be converted to 2147483647
 * @param {Bool} options.sync - Whether to run it in sync mode, defaults to false
 */
var digitalWritePWM = function(pin, dutyCycle, options) {

    // process period
    var period = options.period;
    if (options.frequency) {
        period = 1000 * 1000 / options.frequency;
    }
    if (typeof period === "undefined") {
        period = 20 * 1000;
    }

    // process duty cycle
    var highus = parseInt(period * dutyCycle);
    var lowus = period - highus;

    // process loops to live
    var loops = options.loops || Infinity;
    if (loops === Infinity) {
        loops = -1;
    }

    if (options.sync) {
        Native.setSoftPWMSync(pin, highus, lowus, loops);
    } else {
        Native.setSoftPWM(pin, highus, lowus, loops);
    }
};
