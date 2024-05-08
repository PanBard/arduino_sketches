#ifndef ESP32
#error This code is designed to run on ESP32 platform (ESP32 S2 mini [LOLIN S2 Mini]), not Arduino nor ESP8266! Please check your Tools->Board setting.
#endif

#include "OledStuff.h"
#include "makeJSON.h"
#include "wifiRequest.h"
#include "LoraStuff.h"

void setup() 
{
  // Serial.begin(9600);
  oled_start(); //OLED setup 
  lora_start(); //LORA setup
  start_wifi(); //Wifi setup


}

void loop() 
{
  loraEngineReceiver();
  // Serial.println(get_JSON_string());
}




