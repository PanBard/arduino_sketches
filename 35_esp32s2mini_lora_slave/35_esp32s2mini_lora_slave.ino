#include "lora_crc_traffic.h"
#include "other.h"

void setup() 
{
  lora_start(); //LORA setup   
}

void loop() 
{ 
    loraEngine();
    auto_sender();
}



