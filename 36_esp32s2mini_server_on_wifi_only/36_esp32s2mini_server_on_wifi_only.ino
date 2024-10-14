#include <WiFi.h>

const char* ssid = "HUAWEI-B618-19B7"; // Replace with your Wi-Fi SSID
const char* password = "9N7DDB6QYDE"; // Replace with your Wi-Fi password
const int serverPort = 43219; // Port number for the server

WiFiServer server(serverPort); // Create a server that listens on port 10000


// Set your Static IP address
IPAddress local_IP(192, 168, 8, 578); // Desired static IP
IPAddress gateway(192, 168, 8, 1);    // Your network gateway (usually the router's IP)
IPAddress subnet(255, 255, 255, 0);    // Subnet mask
// IPAddress primaryDNS(8, 8, 8, 8);      // Primary DNS (optional)
// IPAddress secondaryDNS(8, 8, 4, 4);    // Secondary DNS (optional)

// const int tcpPort = 80;                // Your TCP port
const int bufferSize = 1024;           // Example buffer size

void setup() {
    Serial.begin(9600);


    // Configure static IP
    // if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) 
    // {
    //     Serial.println("STA Failed to configure");
    // }
    
    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi!");

     Serial.print("Current ESP IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway (router) IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("Subnet Mask: " );
  Serial.println(WiFi.subnetMask());
  Serial.print("Primary DNS: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.print("Secondary DNS: ");
  Serial.println(WiFi.dnsIP(1));



    Serial.print("TCP Port: ");
    Serial.println(serverPort);

    Serial.print("Buffer Size: ");
    Serial.println(bufferSize);
    
    // Start the server
    server.begin();
    Serial.println("Server started, waiting for clients...");
}

void loop() {
      WiFiClient client = server.available(); // Check if a client has connected
    
    if (client) { // If a new client connects
        Serial.println("New client connected");

        // Send a string message to the client
        String messageToSend = "Hello from ESP32!"; // Example string message
        client.println(messageToSend); // Send the string as response
        
        Serial.print("Sent message: ");
        Serial.println(messageToSend);
        
        client.stop(); // Disconnect the client
        Serial.println("Client disconnected");
    }
}