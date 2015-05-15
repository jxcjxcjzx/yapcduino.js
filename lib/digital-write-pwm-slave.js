// slave for digital lock pulse
var Native = require('../build/Release/yapcduino');

var env = process.env;
var pin = parseInt(env.pin);
var pulse = parseInt(env.pulse);
var period = parseInt(env.period);

while (true) {
    console.log(process.env);
    Native.digitalPulse(pin, pulse, period, 1);
}


