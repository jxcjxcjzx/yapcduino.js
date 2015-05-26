// softpwm
void set_soft_pwm(int pin, int highus, int lowus, int loops_to_live);
void set_soft_pwm_sync(int pin, int highus, int lowus, int loops_to_live);
void unset_soft_pwm(int pin);
int get_soft_pwm_loop_count(int pin, int original_loops_to_live);

// Arduino
void init(void); // must be called before using pin

void hw_pinMode(unsigned char, unsigned char);
void pinMode(unsigned char, unsigned char);
void digitalWrite(unsigned char, unsigned char);
int digitalRead(unsigned char);
int analogRead(unsigned char);
void analogReference(unsigned char mode);
void analogWrite(unsigned char pin, int value);
int pwmfreq_set(unsigned char pin, unsigned int freq);

unsigned long millis(void);
unsigned long micros(void);

void delay(unsigned long);
void delayMicroseconds(unsigned int us);

void delaySched(unsigned long);
void delayMicrosecondsSched(unsigned int us);

unsigned long pulseIn(unsigned char pin, unsigned char state, unsigned long timeout);

void shiftOut(unsigned char dataPin, unsigned char clockPin, unsigned char bitOrder, unsigned char val);
unsigned char shiftIn(unsigned char dataPin, unsigned char clockPin, unsigned char bitOrder);
