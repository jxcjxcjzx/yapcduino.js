var pcduino = require('pcduino');

// load digital API
var API = Object.create(pcduino.digital);

// load analog API
API.analogWrite = pcduino.digital.analogWrite;
API.analogRead = pcduino.digital.analogRead;

// load extra native API
var ExtraNative = require('./../build/Release/yapcduino');
API.setPulse = ExtraNative.setPulse;
