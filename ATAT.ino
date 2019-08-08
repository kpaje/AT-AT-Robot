/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SHOULDERMIN  360 // this is the 'minimum' pulse length count (out of 4096)
#define SHOULDERMAX 420 // this is the 'maximum' pulse length count (out of 4096)
#define KNEEMIN  289 // this is the 'minimum' pulse length count (out of 4096)
#define KNEEMAX  350 // this is the 'maximum' pulse length count (out of 4096)
#define SETMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SETMAX  600 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

#ifdef ESP8266
  Wire.pins(2, 14);   // ESP8266 can use any two pins, such as SDA to #2 and SCL to #14
#endif

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield();



  //Setup starting joint positions
pwm.setPWM(8, 0, map(75, 0, 180, SETMIN, SETMAX));
pwm.setPWM(7, 0, map(70, 0, 180, SETMIN, SETMAX));
pwm.setPWM(6, 0, map(90, 0, 180, SETMIN, SETMAX));
pwm.setPWM(5, 0, map(60, 0, 180, SETMIN, SETMAX));
pwm.setPWM(4, 0, map(110, 0, 180, SETMIN, SETMAX));
pwm.setPWM(3, 0, map(80, 0, 180, SETMIN, SETMAX));
pwm.setPWM(2, 0, map(80, 0, 180, SETMIN, SETMAX));
pwm.setPWM(1, 0, map(60, 0, 180, SETMIN, SETMAX));
pwm.setPWM(0, 0, map(110, 0, 180, SETMIN, SETMAX));

delay(1000);
}





// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop() {
  Serial.println(servonum);
  for (uint16_t pulselen = KNEEMIN; pulselen < KNEEMAX; pulselen++) {
    pwm.setPWM(1, 0, pulselen);
  }
  for (uint16_t pulselen = KNEEMAX; pulselen > KNEEMIN; pulselen--) {
    pwm.setPWM(7, 0, pulselen);
  }
  delay(500);
  for (uint16_t pulselen = SHOULDERMAX; pulselen > SHOULDERMIN; pulselen--) {
    pwm.setPWM(0, 0, pulselen);
  }
  for (uint16_t pulselen = SHOULDERMIN; pulselen < SHOULDERMAX; pulselen++) {
    pwm.setPWM(6, 0, pulselen);
  }
    for (uint16_t pulselen = SHOULDERMAX; pulselen > SHOULDERMIN; pulselen--) {
    pwm.setPWM(0, 0, pulselen);
  }
  delay(500);
  for (uint16_t pulselen = SHOULDERMIN; pulselen < SHOULDERMAX; pulselen++) {
    pwm.setPWM(0, 0, pulselen);
  }
  for (uint16_t pulselen = SHOULDERMAX; pulselen > SHOULDERMIN; pulselen--) {
    pwm.setPWM(6, 0, pulselen);
  }
    for (uint16_t pulselen = SHOULDERMIN; pulselen < SHOULDERMAX; pulselen++) {
    pwm.setPWM(0, 0, pulselen);
  }
  for (uint16_t pulselen = KNEEMAX; pulselen > KNEEMIN; pulselen--) {
    pwm.setPWM(1, 0, pulselen);
  }
  for (uint16_t pulselen = KNEEMIN; pulselen < KNEEMAX; pulselen++) {
    pwm.setPWM(7, 0, pulselen);
  }
  delay(500);

//NEXT SET OF LEGS

  for (uint16_t pulselen = KNEEMAX; pulselen > KNEEMIN; pulselen--) {
    pwm.setPWM(3, 0, pulselen);
  }
  for (uint16_t pulselen = KNEEMIN; pulselen < KNEEMAX; pulselen++) {
    pwm.setPWM(5, 0, pulselen);
  }
  delay(500);
  for (uint16_t pulselen = SHOULDERMIN; pulselen < SHOULDERMAX; pulselen++) {
    pwm.setPWM(2, 0, pulselen);
  }
  for (uint16_t pulselen = SHOULDERMAX; pulselen > SHOULDERMIN; pulselen--) {
    pwm.setPWM(4, 0, pulselen);
  }
    for (uint16_t pulselen = SHOULDERMIN; pulselen < SHOULDERMAX; pulselen++) {
    pwm.setPWM(2, 0, pulselen);
  }
  delay(500);
  for (uint16_t pulselen = SHOULDERMAX; pulselen > SHOULDERMIN; pulselen--) {
    pwm.setPWM(2, 0, pulselen);
  }
  for (uint16_t pulselen = SHOULDERMIN; pulselen < SHOULDERMAX; pulselen++) {
    pwm.setPWM(4, 0, pulselen);
  }
    for (uint16_t pulselen = SHOULDERMAX; pulselen > SHOULDERMIN; pulselen--) {
    pwm.setPWM(2, 0, pulselen);
  }
  for (uint16_t pulselen = KNEEMIN; pulselen < KNEEMAX; pulselen++) {
    pwm.setPWM(3, 0, pulselen);
  }
  for (uint16_t pulselen = KNEEMAX; pulselen > KNEEMIN; pulselen--) {
    pwm.setPWM(5, 0, pulselen);
  }
  delay(500);

  //HEAD


}
