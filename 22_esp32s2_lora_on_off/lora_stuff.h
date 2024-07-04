#include "esp32-hal.h"
#include <LoRa.h>

//---lora pinout
#define ss 12  // for esp32 LOLIN S2 Mini-> SCK:7, MISO: 9, MOSI: 11, NSS: 12, RST: 18
#define rst 5
#define dio0 3
//---lora pinout
#define MESSAGE_LENGTH 50 // max message length
char messageBuffer[MESSAGE_LENGTH];                                                                          
int counter = 0; //count received lora packets 
bool lora_work_properly = false;
int RESTART_count = 100; //restart after this amount message lora send
String inString = "";  // string to hold input from lora
//------------
String parts[3];
//------------

void blink()
{
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(100);                         // wait 
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
}

void splitString(String str, char delimiter, String parts[], int maxParts) 
{
  int partIndex = 0;
  int lastIndex = 0;

  for (int i = 0; i < str.length(); i++) {
    if (str.charAt(i) == delimiter) {
      parts[partIndex++] = str.substring(lastIndex, i);
      lastIndex = i + 1;
      
      if (partIndex == maxParts) // break if max
        break;
    }
  }
    
  if (partIndex < maxParts) {
    parts[partIndex] = str.substring(lastIndex);
  }
}


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

void lora_send_message(const char* message) 
{
  if(lora_work_properly)
  {
    counter++;
    snprintf(messageBuffer, MESSAGE_LENGTH, "ID1 %s", message); //make char message
    //start send packet
    LoRa.beginPacket();
    LoRa.print(messageBuffer);
    LoRa.endPacket();
    //end  send packet
    blink();
  }
}

void loraReceiverForCommand() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {

    blink();

    // read packet
    while (LoRa.available()) { //loop for lora message
      int inChar = LoRa.read();
      inString += (char)inChar;
    }
    splitString(inString, ' ', parts, 3);
    if(parts[0]=="R")
    {
      if(parts[1]=="SWITCH1")
      {
        if(parts[2]=="on")
        {
          switch_on();
        }
        if(parts[2]=="off")
        {
          switch_off();
        }

      }

    }
    inString = ""; // clear received message
  }
}




