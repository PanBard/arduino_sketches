#include "other.h"
#include "lora_crc_traffic.h"


long for4 = 0;

void setup() 
{
  // Serial.begin(9600);
  lora_start(); //LORA setup   
}

void loop() 
{ 
    loraEngine();
    auto_sender();
}


void auto_sender()
{
  if(millis() - for4 > 15000)
  {
    if(!waiting_for_response)
    {
      send_message("test"+String(counter));
      counter ++;
      for4 = millis();
    }

  }
}
