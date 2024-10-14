#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

/*Put your SSID & Password*/
const char* ssid = "HUAWEI-B618-19B7"; // Replace with your Wi-Fi SSID
const char* password = "9N7DDB6QYDE"; // Replace with your Wi-Fi password

WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  
  // Initialize mDNS
  if (!MDNS.begin("elo")) {   // Set the hostname to "esp32.local"
    Serial.println("Error setting up MDNS responder!");
    while(1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  server.send(200, "text/html", "wiadomosc 123"); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}