var p = require('./');
var pwm = new p.SoftPWM(0);
pwm.write(0.5);
