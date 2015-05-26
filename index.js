var Native = require('./build/Release/yapcduino');

var API = {};

Object.keys(Native).forEach(function(method) {
    API[method] = Native[method];
});

API.SoftPWM = require('./lib/softpwm');

module.exports = API;
