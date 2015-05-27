var Native = require('../build/Release/yapcduino');
var C = require('./constant');

var servos = {
    defalut: {
        min: {
            angle: 0,
            pwm: 1
        },
        max: {
            angle: 180,
            pwm: 65
        },
        frequency: 126
    },
    SG90: {
        min: {
            angle: 0,
            pwm: 1
        },
        max: {
            angle: 180,
            pwm: 68
        },
        frequency: 126
    }
};

/**
 * Construct a Servo object
 *
 * @param {Int} pin - pwm pin to use (only 3, 5, 6, 9, 10, and 11)
 * @param {Object} options - Options for servo
 * @param {String} options.type - Type of your servo, available types: ['SG90']
 * @param {Int} options.frequency - Frequency
 */
function Servo(pin, options) {
    options = options || {};
    if (options.type) {
        options = servos[options.type];
    }
    Native.pwmfreq_set(pin, options.frequency);
    this.pin = pin;
    this.min = options.min;
    this.max = options.max;
}

/**
 * Set angle to given angle
 *
 * @param {Int} angle - Angle in degree
 */
Servo.prototype.write = function(angle) {
    this.angle = angle;
    if (angle < this.min.angle || angle > this.max.angle) {
        throw new Error('Angle must in range: ' + this.min.angle + ',' + this.max.angle);
    }
    var rate = (angle - this.min.angle) / (this.max.angle - this.min.angle);
    var pwm = this.min.pwm + rate * (this.max.pwm - this.min.pwm);
    Native.analogWrite(this.pin, parseInt(pwm));
};

/**
 * Return current angle
 */
Servo.prototype.read = function() {
    return this.angle;
};

/**
 * Stop Servo
 */
Servo.prototype.stop = function() {
    Native.analogWrite(this.pin, 0);
};

module.exports = Servo;
