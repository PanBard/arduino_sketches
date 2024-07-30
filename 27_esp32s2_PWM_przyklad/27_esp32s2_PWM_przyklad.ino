#include <ESP32Servo.h>
int APin = 11;
int my_pin = 12;
int low_high_pin = 2;
ESP32PWM pwm;
int freq = 100;  //           <-------------------  you can change frequency (100 is enough for mosfet control)
 for mosfet)
int time_delay = 2000;
void setup() {
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	Serial.begin(115200);
	pwm.attachPin(APin, freq, 10); // 1KHz 8 bit
  pwm.writeScaled(0); // <---  set PWM to 0V
  // pwm.writeScaled(1) <---  set PWM to 3.3V
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(my_pin, OUTPUT);
  pinMode(low_high_pin, OUTPUT); // Ustawienie pinu jako wyjście
  digitalWrite(low_high_pin, HIGH); // Wyłączenie tranzystora (stan HIGH)

}
void blink(int number=1)
{
  	for (int i = 0; i < number; i += 1) 
    {
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(50);                      // wait for a second
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
      delay(50);                      // wait for a second
    }
                  
}

void loop() {
    // blink(1);
    // pwm.writeScaled(0);
    // digitalWrite(my_pin, LOW); 
    // delay(2000);

    // blink(2);
    // pwm.writeScaled(0.1);
    // digitalWrite(my_pin, HIGH); 
    // delay(2000);

    // blink(3);
    // pwm.writeScaled(0.2);
    // digitalWrite(my_pin, LOW); 
    // delay(2000);

    // blink(4);
    // pwm.writeScaled(0.3);
    // digitalWrite(my_pin, HIGH); 
    // delay(2000);

    // blink(5);
    // pwm.writeScaled(0.4);
    // digitalWrite(my_pin, LOW); 
    // delay(2000);

    // blink(6);
    // pwm.writeScaled(0.5);
    // digitalWrite(my_pin, HIGH); 
    // delay(2000);

    // blink(7);
    // pwm.writeScaled(0.6);
    // digitalWrite(my_pin, HIGH); 
    // delay(2000);

    //     blink(8);
    // pwm.writeScaled(0.7);
    // digitalWrite(my_pin, HIGH); 
    // delay(2000);

    //     blink(9);
    // pwm.writeScaled(0.8);
    // digitalWrite(my_pin, HIGH); 
    // delay(2000);

    //     blink(10);
    // pwm.writeScaled(0.9);
    // digitalWrite(my_pin, HIGH); 
    // delay(2000);

    // blink(11);
    // pwm.writeScaled(1);
    // digitalWrite(my_pin, LOW); 
    // delay(2000);

  delay(1000);
    	for (float brightness = 0; brightness <= 1; brightness += 0.001) {
		// Write a unit vector value from 0.0 to 1.0
		  pwm.writeScaled(brightness);
		    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(15);                      // wait for a second
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
      delay(15);                      // wait for a second
	}
  delay(2000);
  pwm.writeScaled(0);
  delay(7000);
  
//   pwm.writeScaled(1);
//     digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
//   delay(100);                      // wait for a second
//   digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
//   delay(100);      
//   digitalWrite(low_high_pin, LOW);
//    delay(time_delay);                // wait for a second
// digitalWrite(low_high_pin, HIGH);

//     pwm.writeScaled(0.75);
//     digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
//   delay(100);                      // wait for a second
//   digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
//   delay(100);                      // wait for a second
//   digitalWrite(low_high_pin, LOW);
//  delay(time_delay);
// digitalWrite(low_high_pin, HIGH);

//      pwm.writeScaled(0.5);
//     digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
//   delay(100);                      // wait for a second
//   digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
//   delay(100);                      // wait for a second
//   digitalWrite(low_high_pin, LOW);
//   delay(time_delay);
// digitalWrite(low_high_pin, HIGH);


//     pwm.writeScaled(0.25);
//     digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
//   delay(100);                      // wait for a second
//   digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
//   delay(100);                      // wait for a second
//   digitalWrite(low_high_pin, LOW);
//   delay(time_delay);
// digitalWrite(low_high_pin, HIGH);

//   pwm.writeScaled(0);
//     digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
//   delay(100);                      // wait for a second
//   digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
//   delay(100);                      // wait for a second
//   digitalWrite(low_high_pin, LOW);
//   delay(time_delay);
// digitalWrite(low_high_pin, HIGH);

// 	for (float brightness = 0; brightness <= 1; brightness += 0.001) {
// 		// Write a unit vector value from 0.0 to 1.0
// 		pwm.writeScaled(1-brightness);
// 		    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
//       delay(4);                      // wait for a second
//       digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
//       delay(4);                      // wait for a second
// 	}
// 		    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
//       delay(1000);                      // wait for a second
//       digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
//       delay(100);                      // wait for a second

}


