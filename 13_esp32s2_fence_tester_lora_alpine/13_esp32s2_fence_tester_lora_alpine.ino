#include "lora_stuff.h"
#include "analog_read.h"

void setup() 
{
  lora_start(); //LORA setup   
}

void loop() 
{
  run_all();
}