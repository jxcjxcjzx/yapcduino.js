var Native = require('../build/Release/yapcduino');
var C = require('./constant');

var servos = {
    default: {
        minPWM: 1,
        maxPWM: 200,
        maxAngle: 180,
        frequency: 390
    },
    SG90: {
        minPWM: 1,
        maxPWM: 200,
        maxAngle: 180,
        frequency: 390
    }
};

/**
 * Construct a Servo object
 *
 * Note: pin(3/9/10/11) support frequency[125-2000]Hz @different dutycycle
 *       pin(5/6) support frequency[195,260,390,520,781] @256 dutycycle
 *
 * @param {Int} pin - pwm pin to use (only 3, 5, 6, 9, 10, and 11)
 * @param {Object} options - Options for servo
 * @param {String} options.type - Type of your servo, available types: ['default', 'SG90']
 * @param {Int} options.minPWM - PWM Value for angle 0, optional if options.type defined
 * @param {Int} options.maxPWM - PWM Value for angle max, optional if options.type defined
 * @param {Int} options.maxAngle - Max angle to reach, defaults 180, optional if options.type defined
 * @param {Int} options.frequency - Frequency, defaults to 390, optional if options.type defined
 */
function Servo(pin, options) {
    options = options || {type: 'default'};
    if (options.type) {
        options = servos[options.type];
    }
    this.pin = pin;
    this.minPWM = options.minPWM;
    this.maxPWM = options.maxPWM;
    this.maxAngle = options.maxAngle || 180;
    this.frequency = options.frequency || 390;
    Native.pwmfreq_set(pin, this.frequency);
}

/**
 * Set angle to given angle
 *
 * @param {Int} angle - Angle in degree
 */
Servo.prototype.write = function(angle) {
    this.angle = angle;
    if (angle < 0 || angle > this.maxAngle) {
        throw new Error('Angle must in range: 0,' + this.maxAngle);
    }
    var rate = angle / this.maxAngle;
    var pwm = this.minPWM + rate * (this.maxPWM - this.minPWM);
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
