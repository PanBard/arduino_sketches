#include <LoRa.h>

//---lora pinout
#define ss 12  // for esp32 LOLIN S2 Mini-> SCK:7, MISO: 9, MOSI: 11, NSS: 12, RST: 18
#define rst 5
#define dio0 3
//---lora pinout
#define MESSAGE_LENGTH 50 // Maksymalna długość wiadomości
char messageBuffer[MESSAGE_LENGTH];                                                                          
int counter = 0; //count received lora packets 
bool lora_work_properly = false;
int RESTART_count = 100; //restart after this amount message lora send

void blink()
{
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(20);                         // wait 
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
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
      delay(5000);
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

void lora_send_message(const char* message) 
{
  if(lora_work_properly)
  {
    counter++;
    snprintf(messageBuffer, MESSAGE_LENGTH, "[%d] %s", counter, message); //make char message
    //start send packet
    LoRa.beginPacket();
    LoRa.print(messageBuffer);
    LoRa.endPacket();
    //end  send packet
    blink();
  }

  if(counter>RESTART_count)
  {
    esp_restart();
  }
 
}




