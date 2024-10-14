#include "other.h"
#include "traffic_lora_administration_for_beacon.h"


void setup() 
{
  // Serial.begin(9600);
  lora_start(); //LORA setup   
}

void loop() 
{ 
    loraEngineReceiver();
    // reset_if_time_to_reset();
}