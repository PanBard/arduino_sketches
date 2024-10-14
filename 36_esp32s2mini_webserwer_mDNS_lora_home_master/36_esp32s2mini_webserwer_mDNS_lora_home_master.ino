#include "lora_crc_traffic.h"
#include "other.h"
#include "wifi_mDNS_webserver.h"

void setup() 
{
  // Serial.begin(9600);
  wifi_mDNS_webserwer_start();
  lora_start(); //LORA setup  

  
}

void loop() 
{
    server.handleClient();
    loraEngine();
    // serial_listener();
}