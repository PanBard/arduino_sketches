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
  info += "Free heap size: "+String(esp_get_free_heap_size()/1000)+" KB"+"\n";
  info += "Minimum free heap size: "+String(esp_get_minimum_free_heap_size()/1000)+" KB"+"\n";
  info += "Reset reason: "+String(esp_reset_reason())+"\n";
  server.send(200, "text/plain", info); 
  info = "";
}

void handle_OnConnect() 
{
  server.send(200, "text/plain", logs); 
  logs = "";
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

void handle_OnSend() 
{
  if (server.hasArg("plain") == false) {
  }
  String body = server.arg("plain");
  lora_send_message(combineMessage("T1","H",body));
  server.send(200, "text/plain", "Receive in esp: "+body); 
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
  if (!MDNS.begin("elo")) {   // Set the hostname to "esp32.local"
    // Serial.println("Error setting up MDNS responder!");
    while(1) {
      delay(1000);
    }
  }
  // Serial.println("mDNS responder started");
  
  server.on("/", handle_OnConnect);
  server.on("/send",HTTP_POST, handle_OnSend);
  server.on("/rssi", handle_OnRSSI);
  server.on("/esp_reset", handle_OnAutokill);
  server.on("/lora_reset", handle_OnResetLoRa);
  server.on("/esp_info", handle_OnInfo);
  server.onNotFound(handle_NotFound);

  server.begin();
  // Serial.println("HTTP server started");
}




