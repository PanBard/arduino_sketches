#include "oled_stuff.h"
#include "lora_stuff.h"
#include "analog_read.h"

void setup() 
{
  Serial.begin(9600);
  oled_start(); //OLED setup 
  lora_start(); //LORA setup   
}

void loop() 
{
  run_all();
}