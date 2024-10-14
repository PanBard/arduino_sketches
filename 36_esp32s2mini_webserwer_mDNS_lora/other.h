long for4 = 0;

void reset_if_time_to_reset()
{
  if(millis()>600000)
  {
    // Serial.println("reset");
    esp_restart();
  }
}

void auto_sender()
{
  if(millis() - for4 > 15000)
  {
    if(!waiting_for_response)
    {
      send_message("T1","master"+String(counter));
      counter ++;
      for4 = millis();
    }
  }
}

void serial_listener()
{
  if (Serial.available() > 0)  // Check if data is available
  {
    String command = Serial.readStringUntil('\n'); // Read the incoming byte
    // Serial.print("Receive message from serial: ");
    // Serial.println(command);
    lora_send_message(combineMessage("T1","H",command));
  }
}
