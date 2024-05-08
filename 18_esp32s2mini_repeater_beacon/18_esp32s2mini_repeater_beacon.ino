#include "lora_stuff.h"
#include "other.h"

void setup() 
{
  Serial.begin(9600);
  lora_start(); //LORA setup   
}

void loop() 
{ 
    loraEngineReceiver();
    reset_if_time_to_reset();
}