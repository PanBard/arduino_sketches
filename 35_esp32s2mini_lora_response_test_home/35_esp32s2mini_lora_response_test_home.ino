#include "other.h"
#include "checksum.h"


void setup() 
{
  // Serial.begin(9600);
  lora_start(); //LORA setup   
}

void loop() 
{ 
    loraEngineReceiver();
    // auto_sender();
    response_handler();
    // reset_if_time_to_reset();
}