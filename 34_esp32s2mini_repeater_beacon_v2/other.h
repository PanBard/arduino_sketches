void reset_if_time_to_reset()
{
  if(millis()>600000)
  {
    // Serial.println("reset");
    esp_restart();
  }
}

void blink()
{
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(100);                         // wait 
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
}