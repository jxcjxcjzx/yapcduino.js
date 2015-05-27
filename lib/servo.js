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

Servo.prototype.write = function(angle) {
    if (angle < this.min.angle || angle > this.max.angle) {
        throw new Error('Angle must in range: ' + this.min.angle + ',' + this.max.angle);
    }
    var rate = (angle - this.min.angle) / (this.max.angle - this.min.angle);
    var pwm = this.min.pwm + rate * (this.max.pwm - this.min.pwm);
    Native.analogWrite(this.pin, parseInt(pwm));
};

Servo.prototype.stop = function() {
    Native.analogWrite(this.pin, 0);
};

module.exports = Servo;
