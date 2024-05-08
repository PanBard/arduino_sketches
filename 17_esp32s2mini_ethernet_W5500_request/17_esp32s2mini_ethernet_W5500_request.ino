#include <Arduino.h>
#include <Ethernet.h>

#include <ESP_SSLClient.h>

#define WIZNET_RESET_PIN 18 // Connect W5500 Reset pin to GPIO 26 of ESP32
#define WIZNET_CS_PIN 12     // Connect W5500 CS pin to GPIO 5 of ESP32
#define WIZNET_MISO_PIN 9  // Connect W5500 MISO pin to GPIO 19 of ESP32
#define WIZNET_MOSI_PIN 11  // Connect W5500 MOSI pin to GPIO 23 of ESP32
#define WIZNET_SCLK_PIN 7  // Connect W5500 SCLK pin to GPIO 18 of ESP32
//  #define SCK_PIN 7
// #define MISO_PIN 9
// #define MOSI_PIN 11
// #define CS_PIN 12
ESP_SSLClient ssl_client;

EthernetClient client;

uint8_t Eth_MAC[] = {0x02, 0xF0, 0x0D, 0xBE, 0xEF, 0x01};

const char* serverAddress = "192.168.8.112";  // Przykładowy adres IP Twojego lokalnego API
const int serverPort = 5164;  // Przykładowy numer portu Twojego lokalnego API

void ResetEthernet()
{
    Serial.println("Resetting WIZnet W5500 Ethernet Board...  ");
    pinMode(WIZNET_RESET_PIN, OUTPUT);
    digitalWrite(WIZNET_RESET_PIN, HIGH);
    delay(200);
    digitalWrite(WIZNET_RESET_PIN, LOW);
    delay(50);
    digitalWrite(WIZNET_RESET_PIN, HIGH);
    delay(200);
}

void networkConnection()
{

    Ethernet.init(WIZNET_CS_PIN);

    ResetEthernet();

    Serial.println("Starting Ethernet connection...");
    Ethernet.begin(Eth_MAC);

    unsigned long to = millis();

    while (Ethernet.linkStatus() == LinkOFF || millis() - to < 2000)
    {
        delay(100);
    }

    if (Ethernet.linkStatus() == LinkON)
    {
        Serial.print("Connected with IP ");
        Serial.println(Ethernet.localIP());
    }
    else
    {
        Serial.println("Can't connect");
    }
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("Start elo");
    networkConnection();

    // ignore server ssl certificate verification
    // ssl_client.setInsecure();

    // Set the receive and transmit buffers size in bytes for memory allocation (512 to 16384).
    // ssl_client.setBufferSizes(1024 /* rx */, 512 /* tx */);

    /** Call setDebugLevel(level) to set the debug
     * esp_ssl_debug_none = 0
     * esp_ssl_debug_error = 1
     * esp_ssl_debug_warn = 2
     * esp_ssl_debug_info = 3
     * esp_ssl_debug_dump = 4
     */
    // ssl_client.setDebugLevel(1);

    // Assign the basic client
    // Due to the basic_client pointer is assigned, to avoid dangling pointer, basic_client should be existed
    // as long as it was used by ssl_client for transportation.
    // ssl_client.setClient(&basic_client);
    go();
    // go2();
}

void go()
{
    Serial.println("---------------------------------");
    Serial.print("Connecting to server...");

      // Sprawdzamy połączenie z serwerem www.google.com
  if (client.connect("www.google.com", 80)) {
    Serial.println("Connected to server");
    client.println("GET / HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("Connection failed");
  }

  // Oczekujemy na odpowiedź serwera
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
  }

  // Zamknięcie połączenia
  client.stop();
  Serial.println("Connection closed");

  // Czekamy przed ponowną próbą połączenia
  delay(1000);
}

void go2()
{
  // Sprawdzamy połączenie z lokalnym API
if (client.connect(serverAddress, serverPort)) {
  Serial.println("Connected to local API");
  client.println("GET /api/api_test HTTP/1.1");  // Dostosuj 'your_endpoint' do rzeczywistego endpointu Twojego API
  client.println("Host: 192.168.8.112");  // Dostosuj adres hosta do adresu Twojego lokalnego API
  client.println("Connection: close");
  client.println();
} else {
  Serial.println("Connection to local API failed");
}

// Oczekujemy na odpowiedź serwera
while (client.connected()) {
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
}

// Zamknięcie połączenia
client.stop();
Serial.println("Connection to local API closed");

// Czekamy przed ponowną próbą połączenia
delay(5000);
}

void loop()
{

}