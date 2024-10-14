#include <LoRa.h>

//---lora pinout
#define ss 12  // for esp32 LOLIN S2 Mini-> SCK:7, MISO: 9, MOSI: 11, NSS: 12, RST: 18
#define rst 5
#define dio0 3
//---lora pinout
                                                              
int counter = 0; //count received lora packets 
bool lora_work_properly = false;

//----
int packetSize;
int inChar;
String inString = "";  // string to hold input from lora
//----

String sending_message = "";
String my_checksum = "";
bool waiting_for_response = false;
long waiting_timestamp = 0;
String message_from_beacon = "";
String receiver = "B";
String me_as_sender = "T1";
String my_message = "testowa_wiadomosc";
String receive_message = "testowa_wiadomosc";
int waiting_time_for_response = 5000;
//------------
String message_parts[3];
//------------


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
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
  } 
}

int checksum_calculator(String str) 
{
  int str_len = str.length() + 1; // Length (with one extra character for the null terminator)
  char char_array[str_len];  // Prepare the character array (the buffer) 
  str.toCharArray(char_array, str_len);  // Copy it over 
  int my_checksum = 0;
  for(char h: char_array){
      my_checksum += int(h);
    }
  return my_checksum;
}

String combineMessage(String receiver, String me_as_sender, String message) 
{
  return receiver + "|" + me_as_sender + "|" + message;
}

void splitString(String str, char delimiter, String message_parts[], int maxParts) 
{
  int partIndex = 0;
  int lastIndex = 0;
  for (int i = 0; i < str.length(); i++) 
  {
    if (str.charAt(i) == delimiter) 
    {
      message_parts[partIndex++] = str.substring(lastIndex, i);
      lastIndex = i + 1;
      if (partIndex == maxParts) break;// break if max
    }
  }
  if (partIndex < maxParts) 
  {
    message_parts[partIndex] = str.substring(lastIndex);
  }
}

void clearStringArray(String message_parts[], int size) 
{
  for (int i = 0; i < size; i++) 
  {
    message_parts[i] = "";  // Set each element to an empty string
  }
}


void send_message(String message)
{
  my_message = message;
  sending_message = combineMessage(receiver,me_as_sender,message);
  my_checksum = String(checksum_calculator(combineMessage("HB",me_as_sender,message)));
  waiting_for_response = true;
  lora_send_message(sending_message);
  waiting_timestamp = millis();
}

void send_message_again()
{
  waiting_for_response = true;
  lora_send_message(sending_message);
  waiting_timestamp = millis();
}

void response_handler()
{
  if(waiting_for_response)
  {

    if(my_checksum == message_parts[2])
    {
      waiting_for_response = false;
      my_checksum = "";
    }
    else if((millis() - waiting_timestamp > waiting_time_for_response) && waiting_for_response)
    {
      send_message_again();

    }
  }
}

void receiving_handler_to_return_cheksum()
{
 lora_send_message( combineMessage(message_parts[1], me_as_sender, String(checksum_calculator(inString))) );
}

void loraEngineReceiver() 
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    while (LoRa.available()) //loop for lora message
    { 
      int inChar = LoRa.read();
      inString += (char)inChar;
    }

    splitString(inString, '|', message_parts, 3);

    if(message_parts[0]==me_as_sender && message_parts[1]==receiver)
    {
      message_from_beacon = message_parts[2];
      delay(100);
      if(waiting_for_response)
      {
        response_handler();
      }
      else
      {
        receiving_handler_to_return_cheksum();
      }
      
    }  
    clearStringArray(message_parts, 3);
    inString = ""; // clear received message
  }
}

void  loraEngine()
{
    loraEngineReceiver();
    response_handler();
    delay(10);
}
