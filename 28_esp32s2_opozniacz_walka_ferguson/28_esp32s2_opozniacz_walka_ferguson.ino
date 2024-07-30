#include <ESP32Servo.h>
int APin = 11;
int freq = 100;  //           <-------------------  you can change frequency (100 is enough for mosfet control)
ESP32PWM pwm;

void run()
{
   	for (float pwm_value = 0; pwm_value <= 1; pwm_value += 0.001) {
		  pwm.writeScaled(pwm_value);
      delay(5);                      // wait for a second
    }
}

void setup() {
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	pwm.attachPin(APin, freq, 10); // 1KHz 8 bit
  pwm.writeScaled(0); // <---  set PWM to 0V
  // pwm.writeScaled(1) <---  set PWM to 3.3V
  run();
}

void loop() {}




