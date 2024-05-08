#include <LoRa.h> // by Sandeep Mistry

//---lora
#define ss 12  //MOSI: 11, MISO: 9, SCK: 7
#define rst 5
#define dio0 3
//---lora

String inString = "";  // string to hold input from lora
int counter = 0; //count received lora packets 
long intervalTime = 0; //for time measurement between received lora packet

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

void loraEngineReceiver() {
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
      oled_display_lora_content(inString, LoRa.packetRssi(),intervalTime,counter );
      counter++;
      intervalTime = millis();
    }
    // Serial.print(" Packet: ");
    // Serial.println(inString);
    // Serial.print("' with RSSI ");
    // Serial.println(LoRa.packetRssi());
    
    inString = ""; // clear received message
    // intervalTime = millis();
  }
}

void lora_start() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  LoRa.setPins(ss, rst, dio0);
   if (!LoRa.begin(433E6)) {
    while (1) {
      oled_display("Starting LoRa failed!");
      // Serial.println("Starting LoRa failed!");
      // Serial.print("MOSI: ");
      // Serial.println(MOSI);
      // Serial.print("MISO: ");
      // Serial.println(MISO);
      // Serial.print("SCK: ");
      // Serial.println(SCK);
      // Serial.print("SS: ");
      // Serial.println(SS);
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(1000);                      // wait for a second
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
      delay(10000);
    };
  }
  oled_display("Status: ok");
  // Serial.println("LoRa status: ok");
}
