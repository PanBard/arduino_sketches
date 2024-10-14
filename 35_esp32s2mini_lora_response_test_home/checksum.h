#include "esp32-hal.h"
#include "lora_stuff.h"

String sending_message = "";
int my_checksum = 0;
bool waiting_for_response = false;
long waiting_timestamp = 0;
String message_from_beacon = "";
String receiver = "T1";
String me_as_sender = "H";
String my_message = "testowa_wiadomosc";
String receive_message = "testowa_wiadomosc";
int waiting_time_for_response = 5000;

//------------
String message_parts[3];
//------------


long for4 = 0;


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
  my_checksum = checksum_calculator(sending_message);
  waiting_for_response = true;
  lora_send_message(sending_message);
  waiting_timestamp = millis();
}

void response_handler()
{
  if(waiting_for_response)
  {
    if(String(my_checksum) == message_parts[2])
    {
      waiting_for_response = false;
      my_checksum = 0;
    }
    else if(millis() - waiting_timestamp > waiting_time_for_response)
    {
      send_message(my_message);
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
    response_handler();
    if(message_parts[0]=="HB")
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
      // clearStringArray(message_parts, 3);
    }  
    inString = ""; // clear received message
  }
}

// void auto_sender()
// {
//   if(millis() - for4 > 15000)
//   {
//     send_message("test"+String(counter));
//     counter ++;
//     for4 = millis();
//   }
// }

// void loraEngineReceiver() 
// {
//   int packetSize = LoRa.parsePacket();
//   if (packetSize) 
//   {
//     while (LoRa.available()) //loop for lora message receiver
//     { 
//       int inChar = LoRa.read();
//       receive_message += (char)inChar;
//     }
//     response_handler();
//     receive_message = ""; // clear received message
//   }
// }