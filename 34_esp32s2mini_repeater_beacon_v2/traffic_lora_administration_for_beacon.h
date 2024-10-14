#include "lora_stuff.h"

//------------
String message_parts[3];
//------------



String combineMessage(String receiver, String sender, String message) 
{
  return receiver + "|" + sender + "|" + message;
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

void send_response()
{
  lora_send_message( combineMessage(message_parts[1],"B",message_parts[1]) );
}

void forward_message_to_home()
{
  lora_send_message( combineMessage("HB",message_parts[1],message_parts[2]) );
}

void forward_message_from_home_to_edge()
{
  lora_send_message( combineMessage(message_parts[0],"B",message_parts[2]) );
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
    if(message_parts[0]=="B")
    {
      // send_response();
      delay(200);
      forward_message_to_home();
      clearStringArray(message_parts, 3);
    }  
    else if(message_parts[1]=="H")
    {
      // send_response();
      delay(200);
      forward_message_from_home_to_edge();
      clearStringArray(message_parts, 3);
    }  
    
    inString = ""; // clear received message
  }
}

