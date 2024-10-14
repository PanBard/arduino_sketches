#include "lora_crc_traffic.h"
#include "other.h"
void setup() 
{
   Serial.begin(9600);
  lora_start(); //LORA setup   
}

void loop() 
{ 
    loraEngine();
    auto_sender();
}



