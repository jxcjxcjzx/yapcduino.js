var Native = require('../build/Release/yapcduino');
var pcduino = require('pcduino');

function SoftPWM(pin) {
    this.pin = pin;
    pcduino.pinMode(pin, pcduino.digital.OUTPUT);
}

/**
 * Attach the SoftPWM instance to a new pin
 *
 */
SoftPWM.prototype.attach = function(pin) {
    if (this.pin != null) {
        this.detach();
    }
    this.pin = pin;
    return this.dutyCycle;
};

/**
 * Detach the SoftPWM instance from original pin (will unset output of original pin and set this.pin to null)
 *
 */
SoftPWM.prototype.detach = function() {
    if (this.pin != null) {
        Native.unsetSoftPWM(this.pin);
    }
    this.pin = null;
};

/**
 * Get count of loops of the pin since last write
 *
 */
SoftPWM.prototype.getLoopCount = function() {
    return Native.getSoftPWMLoopCount(this.pin, this.originalLoopsToLive || -1);
};

/**
 * Writes a PWM wave to a p in (using digitalWrite).
 * To stop, simply call pwm.detach();
 *
 * @see http://www.arduino.cc/en/Tutorial/PWM
 * @see http://www.arduino.cc/en/Reference/analogWrite
 * @param {Float} dutyCycle - Duty Cycle [0, 1]
 * @param {Object} options - Options for PWM
 * @param {Int} options.period - Period (in us), defaults to 20 * 1000
 * @param {Int} options.frequency - Frequency, period will be ignored if frequency set
 * @param {Number} options.loops - (loops to live) How many loops should it run, defaults to Infinity (actually is 2147483647), note that -1 will be converted to 2147483647
 * @param {Bool} options.sync - Whether to run it in sync mode, defaults to false
 */
SoftPWM.prototype.write = function(dutyCycle, options) {
    var pin = this.pin;
    options = options || {};
    this.originalLoopsToLive = options.loops;
    this.dutyCycle = dutyCycle;

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

/**
 * Read last set dutyCycle (will return undefined if not set)
 *
 */
SoftPWM.prototype.read = function() {
    return this.dutyCycle;
};

module.exports = SoftPWM;
