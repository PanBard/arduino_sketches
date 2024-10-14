#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

/*Put your SSID & Password*/
const char* ssid = "HUAWEI-B618-19B7"; // Replace with your Wi-Fi SSID
const char* password = "9N7DDB6QYDE"; // Replace with your Wi-Fi password

WebServer server(80);



void handle_OnInfo()
{
  String info = "";
  // info += "Boot mode: "+String(ESP.getBootMode())+"\n";
  info += "Chip model: "+String(ESP.getChipModel())+"\n";
  info += "CPU frequency: "+String(ESP.getCpuFreqMHz())+" MHz"+"\n";
  info += "Heap size: "+String(ESP.getHeapSize()/1000)+" KB"+"\n";
  info += "Free heap size: "+String(esp_get_free_heap_size()/1000)+" KB"+"\n";
  info += "Minimum free heap size: "+String(esp_get_minimum_free_heap_size()/1000)+" KB"+"\n";
  info += "Psram size: "+String(ESP.getPsramSize()/1000)+" KB"+"\n";
  info += "Flash Chip Size: "+String(ESP.getFlashChipSize()/1000)+" KB"+"\n";
  info += "Sketch Size: "+String(ESP.getSketchSize()/1000)+" KB"+"\n";
  info += "Free Sketch Space: "+String(ESP.getFreeSketchSpace()/1000)+" KB"+"\n";
  info += "Current ESP32 IP: "+String(WiFi.localIP())+"\n";
  info += "ESP32 MAC Address: "+String(WiFi.macAddress())+"\n";
  info += "gatewayIP: "+String(WiFi.gatewayIP())+"\n";
  info += "dnsIP: "+String(WiFi.dnsIP())+"\n";
  info += "broadcastIP: "+String(WiFi.broadcastIP())+"\n";
  info += "networkID: "+String(WiFi.networkID())+"\n";
  info += "Reset reason: "+String(esp_reset_reason())+" [https://docs.espressif.com/projects/arduino-esp32/en/latest/api/reset_reason.html]"+"\n";
  unsigned long runtimeMillis = millis();
  unsigned long seconds = runtimeMillis / 1000;
  info += "Runtime: " + String(seconds / 3600) +"h "+ String((seconds % 3600) / 60) +"m "+ String(seconds % 60)+"s"+ "\n";
  server.send(200, "text/plain", info); 
  info = "";
  runtimeMillis = 0;
  seconds = 0;
}

void handle_OnConnect() 
{
  server.send(200, "text/plain", logs); 
  logs = "";
}

void handle_OnEnableCRC() 
{
  server.send(200, "text/plain", "CRC in LoRa module was enabled."); 
  delay(500);
  LoRa.enableCrc();
}

void handle_OnDisableCRC() 
{
  server.send(200, "text/plain", "CRC in LoRa module was disabled."); 
  delay(500);
  LoRa.disableCrc();
}

void handle_OnAutokill() 
{
  server.send(200, "text/plain", "Resetting ESP."); 
  delay(500);
  ESP.restart();
}

void handle_OnResetLoRa() 
{
  server.send(200, "text/plain", "Resetting LoRa module."); 
  delay(500);
  lora_restart();
}

void handle_OnRSSI() 
{
  int rssi = WiFi.RSSI();
  server.send(200, "text/plain", String(rssi)); 
}

// void handle_OnSend() 
// {
//   if (server.hasArg("plain") == false) {
//   }
//   String body = server.arg("plain");
//   lora_send_message(combineMessage("T1","H",body));
//   server.send(200, "text/plain", "Receive in esp: "+body); 
// }

void handle_OnSend() 
{
  if (server.hasArg("plain") == false) {
  }
  String body = server.arg("plain");
  lora_send_message(body);
  server.send(200, "text/plain", "Receive"); 
}

void handle_OnSendCRC() 
{
  if (server.hasArg("plain") == false) {
  }
  String body = server.arg("plain");
  send_message_CRC(body);
  server.send(200, "text/plain", "Receive"); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

void wifi_mDNS_webserwer_start() {
  // Serial.println("Connecting to ");
  // Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    // Serial.print(".");
  }
  // Serial.println("");
  // Serial.println("WiFi connected..!");
  
  // Initialize mDNS
  if (!MDNS.begin("esp_baza")) {   // Set the hostname to "esp32.local"
    // Serial.println("Error setting up MDNS responder!");
    while(1) {
      delay(1000);
    }
  }
  // Serial.println("mDNS responder started");
  
  server.on("/", handle_OnConnect);
  server.on("/send",HTTP_POST, handle_OnSend);
  server.on("/send_with_CRC",HTTP_POST, handle_OnSendCRC);
  server.on("/rssi", handle_OnRSSI);
  server.on("/esp_reset", handle_OnAutokill);
  server.on("/lora_reset", handle_OnResetLoRa);
  server.on("/crc_on", handle_OnEnableCRC);
  server.on("/crc_off", handle_OnDisableCRC);
  server.on("/esp_info", handle_OnInfo);
  server.onNotFound(handle_NotFound);

  server.begin();
  // Serial.println("HTTP server started");
}




