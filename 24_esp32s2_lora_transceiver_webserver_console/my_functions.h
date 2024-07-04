
void start_my_functions() 
{
    pinMode(LED_BUILTIN, OUTPUT);
}

void blink() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(20);                         // wait 
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
}

void reset_if_time_to_reset()
{
  unsigned long currentMillis = millis();
  unsigned long millis_interval = 3600000;
  if(currentMillis>millis_interval)
  {
    esp_restart();
  }
}

