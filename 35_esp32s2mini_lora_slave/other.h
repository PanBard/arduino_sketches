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
  if(millis() - for4 > 30000)
  {
    if(!waiting_for_response)
    {
      send_message("test"+String(counter));
      counter ++;
      for4 = millis();
    }

  }
}