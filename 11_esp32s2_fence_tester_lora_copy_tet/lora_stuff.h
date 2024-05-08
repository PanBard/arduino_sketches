#include <LoRa.h>

//---lora pinout
#define ss 12  // for esp32 LOLIN S2 Mini-> SCK:7, MISO: 9, MOSI: 11, NSS: 12, RST: 18
#define rst 5
#define dio0 3
//---lora pinout


long lastSendTime = 0;        // last send time for test sender                
int interval_in_miliseconds = 3000; //  time between repeat seding packet    <<<<------ MANUAL SETUP                                                                <<<<------ MANUAL SETUP
int counter = 0; //count received lora packets 
bool lora_work_properly = false;

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
      Serial.println("Starting LoRa failed!");
      Serial.print("MOSI: ");
      Serial.println(MOSI);
      Serial.print("MISO: ");
      Serial.println(MISO);
      Serial.print("SCK: ");
      Serial.println(SCK);
      Serial.print("SS: ");
      Serial.println(SS);
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(1000);                      // wait for a second
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
      oled_display_one_message("problem with lora!");
      lora_work_properly = false;
      delay(5000);
  }
  else
  {
    lora_work_properly = true;
    Serial.println("LoRa status: ok");
    oled_display_one_message("lora work properly :)");
    blink();
    delay(100);
    blink();
    delay(100);
    blink();
  }
  
}

void lora_send_message(String message) 
{
  if(lora_work_properly)
  {
    counter++;
    message = "["+String(counter)+"] "+message;
    //start send packet
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
    //end  send packet
    blink();
    message = "Sending: "+message;
    oled_display_one_message(message);
  }
 
}

// void lora_send_test_message_repetitively() 
// {
//    if (millis() - lastSendTime > interval_in_miliseconds)
//    {    
//       counter++;
//       lora_send_message("jazda "+String(counter));
//       lastSendTime = millis(); //set new send time    
//     }
// }



