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