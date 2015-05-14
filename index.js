var pcduino = require('pcduino');

var API = Object.create(pcduino.digital);
API.analogWrite = pcduino.digital.analogWrite;
API.analogRead = pcduino.digital.analogRead;
