#include <LoRa.h>

//---lora
#define ss 12  // for esp32 LOLIN S2 Mini-> SCK:7, MISO: 9, MOSI: 11, NSS: 12, RST: 18
#define rst 16
#define dio0 2
//---lora

int counter = 0; //count received lora packets 
long intervalTime = 0; //for time measurement between received lora packet
String message = ""; // save message from lora
String logs = ""; //log all lora message to one string

void lora_start() 
{
  LoRa.setPins(ss, rst, dio0);
   if (!LoRa.begin(433E6)) {
    while (1) {      
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(1000);                      // wait for a second
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
      delay(10000);
    };
  }
  // Serial.println("LoRa status: ok");
}

void lora_send_message(String message_to_send) 
{
  LoRa.beginPacket();
  LoRa.print(message_to_send);
  LoRa.endPacket();
  logs += ("Sent: "+message_to_send+"\n");
  blink();
}

void loraEngineReceiver() 
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    blink();
    while (LoRa.available()) //loop for lora message receiver
    { 
      int inChar = LoRa.read();
      message += (char)inChar;
    }

    logs += ("Received: "+message+"\n");
    message = ""; // clear received message
    intervalTime = millis();

    // Serial.print("Received packet: ");
    // Serial.print(message);
    // Serial.println(" (with RSSI "+String(rssi)+")");
  }
}




