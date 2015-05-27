var Native = require('./build/Release/yapcduino');
var C = require('./lib/constant');

function Pcduino(options) {
    options = options || {};
    if (options.global) {
        Object.keys(Pcduino).forEach(function(k) {
            global[k] = Pcduino[k];
        });
    }
};

// Load APIs (static)

Object.keys(Native).forEach(function(method) {
    Pcduino[method] = Native[method];
});

Object.keys(C).forEach(function(c) {
    Pcduino[c] = C[c];
});

Pcduino.SoftPWM = require('./lib/softpwm');
Pcduino.Servo = require('./lib/servo');

module.exports = Pcduino;
