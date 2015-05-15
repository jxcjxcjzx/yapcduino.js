// slave for digital lock pulse
var Native = require('../build/Release/yapcduino');

var argv = process.argv;
var pin = parseInt(argv[2]);
var pulse = parseInt(argv[3]);
var period = parseInt(argv[4]);

console.log({pin: pin, pulse: pulse, period: period});

while (true) {
    // Native.digitalPulse(pin, pulse, period, 1);
}


