#include <ESP32Servo.h>

int APin = 11;
int freq = 100;  //           <-------------------  you can change frequency (100 is enough for mosfet control)
ESP32PWM pwm;

// void run()
// {
//    	for (float pwm_value = 0; pwm_value <= 1; pwm_value += 0.001) {
// 		  pwm.writeScaled(pwm_value);
//       delay(5);                      // wait for a second
//     }
// }


void run()
{

  	// for (float pwm_value = 0; pwm_value <= 5; pwm_value += 1) {
		//   pwm.writeScaled(1);
    //   delay(100);     
    //   pwm.writeScaled(0);
    //   delay(200);            
    // }

     pwm.writeScaled(1);
      delay(1000);     
    pwm.writeScaled(0);
      delay(600); 

      for (float pwm_value = 0; pwm_value <= 2; pwm_value += 1) {
		  pwm.writeScaled(1);
      delay(100);     
      pwm.writeScaled(0);
      delay(500);            
    }

    	for (float pwm_value = 0; pwm_value <= 3; pwm_value += 1) {
		  pwm.writeScaled(1);
      delay(150);     
      pwm.writeScaled(0);
      delay(600);            
    }


    	for (float pwm_value = 0; pwm_value <= 5; pwm_value += 1) {
		  pwm.writeScaled(1);
      delay(200);     
      pwm.writeScaled(0);
      delay(500);            
    }

    	for (float pwm_value = 0; pwm_value <= 5; pwm_value += 1) {
		  pwm.writeScaled(1);
      delay(300);     
      pwm.writeScaled(0);
      delay(400);            
    }

      	for (float pwm_value = 0; pwm_value <= 5; pwm_value += 1) {
		  pwm.writeScaled(1);
      delay(400);     
      pwm.writeScaled(0);
      delay(400);            
    }


   	for (float pwm_value = 0; pwm_value <= 5; pwm_value += 1) {
		  pwm.writeScaled(1);
      delay(800);     
      pwm.writeScaled(0);
      delay(800);            
    }

    pwm.writeScaled(1);
}


// void run()
// {
//    	for (float pwm_value = 0.75; pwm_value <= 0.85; pwm_value += 0.0001) {
// 		  pwm.writeScaled(pwm_value);
//       delay(5);                      // wait for a second
//     }
// }
// void run()
// {
// pwm.writeScaled(0.8);
// delay(800);
// pwm.writeScaled(0);
// delay(800);

//    	for (float pwm_value = 0.8; pwm_value <= 1; pwm_value += 0.05) {
// 		  pwm.writeScaled(pwm_value);
//       delay(400);   
//       pwm.writeScaled(0);
//       delay(800);                   // wait for a second
//     }

//     pwm.writeScaled(1);
// }

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	pwm.attachPin(APin, freq, 10); // 1KHz 8 bit
  pwm.writeScaled(0); // <---  set PWM to 0V
  // pwm.writeScaled(1) <---  set PWM to 3.3V
  run();
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(20);  
}

void loop() {}




