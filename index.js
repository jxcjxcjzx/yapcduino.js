var Native = require('./build/Release/yapcduino');
var C = require('./lib/constant');

var API = {};

Object.keys(Native).forEach(function(method) {
    API[method] = Native[method];
});

Object.keys(C).forEach(function(c) {
    API[c] = C[c];
});

API.SoftPWM = require('./lib/softpwm');

module.exports = API;
