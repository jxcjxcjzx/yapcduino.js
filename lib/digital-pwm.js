var ExtraNative = require('../build/Release/yapcduino');
var child_process = require('child_process');

var processPool = {};

// TODO: 可能叫这个名字也不是太妥当，应该再想一个，因为只是把一个值用 pwm 写了出来
/**
 * Writes a value PWM wave to a pin (using digitalWrite).
 * It will fork Node.js process and run loops there to make the PWM keep outputting.
 * To stop, simply call pcduino.digitalPWM(pin, 0)
 *
 * @see http://www.arduino.cc/en/Tutorial/PWM
 * @see http://www.arduino.cc/en/Reference/analogWrite
 * @param {Int} pin - Pin ID
 * @param {Float} dutyCycle - Duty Cycle [0, 1]
 * @param {Int} period - Period (in us), defaults to 20 * 1000
 */
var digitalPWM = function(pin, dutyCycle, period) {
    if (typeof period === "undefined") {
        period = 20 * 1000;
    }
    var pulse = parseInt(period * dutyCycle);
    processPool[pin] = child_process.fork('./digital-pwm-slave.js', [], {env: {
        pin: pin,
        pulse: pulse,
        period: period
    }});
};

module.exports = digitalPWM;
