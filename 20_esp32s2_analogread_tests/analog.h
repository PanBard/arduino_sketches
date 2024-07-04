#include "USBCDC.h"
#define analog_pin 3 //analogpin x pin 3
#define MESSAGE_LENGTH 10 // max message lenght
char message[MESSAGE_LENGTH];
int analog_value;
long int current_time = 0;
long int last_update_time_for_max_value = millis();
long int last_update_time_for_current_value = millis();
int record_min = 8000;
int record_max = 0;
int interval_to_measure_max_difference = 3000; // <----------------------------------- MANUAL SETUP  - interval between displaying value
int interval_for_current_analog_value = 200; // <----------------------------------- MANUAL SETUP  - interval between displaying value
int max_difference = 0;
int analog_value_to_display=0;
int current_difference=0;
void analog_start()
{
  pinMode(LED_BUILTIN, OUTPUT);
  // Serial.begin(9600);
}

void blink()
{
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(200);                         // wait 
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
}


void handle_analogRead() 
{
  // Serial.println(current_time);
  // Serial.println(current_time/1000);
  // Serial.println();
  // oled_update(String(analogRead(analog_pin)));

  current_time=millis();
    if(current_time-last_update_time_for_max_value>interval_to_measure_max_difference)
  {
    // snprintf(message, MESSAGE_LENGTH, "raw value: %d" , ); //convert int to char
    // Serial.print("raw value: ");
    // Serial.println(record_max-record_min);
    max_difference = record_max-record_min;
    last_update_time_for_max_value=millis();
    record_max=0;
    record_min=8000;
    blink();
  }
  analog_value = analogRead(analog_pin);
  if(analog_value > record_max)
  {
    record_max=analog_value;
  }
  if(analog_value < record_min)
  {
    record_min=analog_value;
  }

  if(current_time-last_update_time_for_current_value>interval_for_current_analog_value)
  {
    analog_value_to_display = analog_value;
    current_difference = record_max-record_min;
    last_update_time_for_current_value=millis();
  }

    oled_display_content(max_difference,  interval_to_measure_max_difference,   current_time-last_update_time_for_max_value,   analog_value_to_display,  record_min,  record_max, current_difference );

}