var Native = require('../build/Release/yapcduino');
var child_process = require('child_process');
var pcduino = require('pcduino');
var path = require('path');

var processPool = {};
// kill all child process when this process is going to exit
process.on('exit', function() {
    Object.keys(processPool).forEach(function(key) {
        processPool[key].kill('SIGKILL');
    });
});

/**
 * Writes a PWM wave to a pin (using digitalWrite).
 * If keepLooping is true, it will fork Node.js process
 * and run loops there to make the PWM keep outputting.
 * These child Nodes are still whole new instances of V8.
 * Assume at least 30ms startup and 10mb memory for each new Node.
 * To stop, simply call pcduino.digitalWritePWM(pin, 0)
 *
 * @see http://www.arduino.cc/en/Tutorial/PWM
 * @see http://www.arduino.cc/en/Reference/analogWrite
 * @param {Int} pin - Pin ID
 * @param {Float} dutyCycle - Duty Cycle [0, 1]
 * @param {Int} period - Period (in us), defaults to 20 * 1000
 * @param {Boolean} keepLooping - Whether to keep looping, defaults to true
 */
var digitalWritePWM = function(pin, dutyCycle, period, keepLooping) {
    // force to kill the child process now
    if (processPool[pin]) {
        processPool[pin].kill('SIGKILL');
        processPool[pin] = null;
    }

    if (dutyCycle === 0) {
        pcduino.digital.digitalWrite(pin, pcduino.digital.LOW);
        return;
    }

    if (dutyCycle === 1) {
        pcduino.digital.digitalWrite(pin, pcduino.digital.HIGH);
        return;
    }

    // parse arguments
    if (typeof period === "undefined") {
        period = 20 * 1000;
    }
    var pulse = parseInt(period * dutyCycle);
    if (typeof keepLooping === "undefined") {
        keepLooping = true;
    }

    // write once
    if (!keepLooping) {
        Native.digitalPulse(pin, pulse, period, 1);
        return;
    }

    // keep looping
    var slave = path.join(__dirname, 'digital-write-pwm-slave.js');
    processPool[pin] = child_process.fork(slave, [pin, pulse, period]);
};

module.exports = digitalWritePWM;
