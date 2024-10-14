

String sending_message = "";
int my_checksum = 0;
bool waiting_for_response = false;
long waiting_timestamp = 0;
String message_from_beacon = "";
String receiver = "B";
String me_as_sender = "T1";
String message = "testowa_wiadomosc";
String receive_message = "testowa_wiadomosc";
int waiting_time_for_response = 5000;

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

void send_message(String receiver, String me_as_sender, String message)
{
  sending_message = combineMessage(receiver,me_as_sender,message);
  my_checksum = checksum_calculator(sending_message);
  waiting_for_response = true;
  lora_send_message(sending_message);
  waiting_timestamp = millis();
}

void response_handler(String receiver, String me_as_sender, String message)
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
      send_message(receiver,me_as_sender,message);
      my_checksum = checksum_calculator(sending_message);
      waiting_for_response = true;
      waiting_timestamp = millis();
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
    if(message_parts[0]==me_as_sender)
    {
      message_from_beacon = message_parts[2]
      delay(200);
      receiving_handler_to_return_cheksum();
      clearStringArray(message_parts, 3);
    }  
    inString = ""; // clear received message
  }
}

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