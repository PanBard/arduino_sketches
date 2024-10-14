#include "lora_crc_traffic.h"
#include "other.h"
void setup() 
{
   Serial.begin(9600);
  lora_start(); //LORA setup   
  delay(2000);
  Serial.println("master home listen ...");
}

void loop() 
{ 
    loraEngine();
    serial_listener();
    // auto_sender();
}



