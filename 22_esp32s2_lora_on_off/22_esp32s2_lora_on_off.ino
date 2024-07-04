#include "reset_function.h"
#include "switch_stuff.h"
#include "lora_stuff.h"



void setup() 
{
  // Serial.begin(9600);
  lora_start(); //LORA setup  
  pin_start(); 
}

void loop() 
{ 
  loraReceiverForCommand();
  reset_if_time_to_reset();

}