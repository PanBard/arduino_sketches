#ifndef ESP32
#error This code is designed to run on ESP32 platform (ESP32 S2 mini [LOLIN S2 Mini]), not Arduino nor ESP8266! Please check your Tools->Board setting.
#endif

#include "my_functions.h"
#include "lora_stuff.h"
#include "webserver_stuff.h"

void setup() {
  // Serial.begin(9600);
  start_my_functions();
  lora_start(); //LORA setup
  wifi_and_webserver_start(); //WIFI setup
}

void loop() {
  loraEngineReceiver();//lora
  dnsServer.processNextRequest();//DNS
  server.handleClient(); //HTTP
  reset_if_time_to_reset();
}

