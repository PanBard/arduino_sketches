#include "lora_stuff.h"
#include "analog_read.h"

void setup() 
{
  // Serial.begin(9600);
  lora_start(); //LORA setup   

}

void loop() 
{ 
    detect_fence_impulse();
    reset_if_time_to_reset();
}