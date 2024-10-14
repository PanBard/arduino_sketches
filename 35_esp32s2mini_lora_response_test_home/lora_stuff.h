#include "esp32-hal.h"
#include <LoRa.h>


//---lora pinout
#define ss 12  // for esp32 LOLIN S2 Mini-> SCK:7, MISO: 9, MOSI: 11, NSS: 12, RST: 18
#define rst 5
#define dio0 3
//---lora pinout
// #define MESSAGE_LENGTH 50 // max message length
// char messageBuffer[MESSAGE_LENGTH];   
// char recieveBuffer[MESSAGE_LENGTH];                                                                
int counter = 0; //count received lora packets 
bool lora_work_properly = false;
// int RESTART_count = 100; //restart after this amount message lora send

//----
int packetSize;
int inChar;
String inString = "";  // string to hold input from lora
//----



void lora_start() 
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  LoRa.setPins(ss, rst, dio0);

   if (!LoRa.begin(433E6)) 
   {      
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(1000);                      // wait for a second
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
      lora_work_properly = false;
      delay(1000);
  }
  else
  {
    LoRa.setTxPower(20);
    LoRa.enableCrc(); // <-----------CRC

    lora_work_properly = true;
    blink();
    delay(100);
    blink();
    delay(100);
    blink();
  }
}

void lora_check_status() 
{ 
   if (!LoRa.begin(433E6)) 
   {      
      lora_work_properly = false;
    }
  else
  {
    lora_work_properly = true;
  }
}

void lora_send_message(String message) 
{
  if(lora_work_properly)
  {
    // counter++;
    // snprintf(messageBuffer, MESSAGE_LENGTH, "R %d", message); //make char message
    //start send packet
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
    //end  send packet
    // blink();
    // inString = ""; // clear received message
    // Serial.println(inString);
    // Serial.println(message);
  } 
}

// void loraEngineReceiver() 
// {
//   packetSize = LoRa.parsePacket();
//   if (packetSize) 
//   {
//     blink();
//     inString = "R ";
//     while (LoRa.available()) // read packet and loop for lora message
//     { 
//       inChar = LoRa.read();
//       inString += (char)inChar;
//       // inString.toCharArray(recieveBuffer, inString.length());
//     }
//     delay(100);
//     lora_send_message();
//     // Serial.println(recieveBuffer);
//     // Serial.println(inString);
//   }
// }




