void blink() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(20);                         // wait 
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
}

int max_turn_number = 25;
int counter = 0;
int counter_job = 0;
long m = millis();
int analog_pin = 0;
int neutral_value = 590;            // <- SETUP
int range_value = 20;               // <- SETUP
int neutral_value_max = neutral_value+range_value;
int neutral_value_min = neutral_value-range_value;
bool sensor_not_detected = false;

void halotron_run() 
{
  int wartosc_cyfrowa = 0; 
  int wartosc_analogowa = 0;

  // wartosc_cyfrowa = digitalRead(3);
  wartosc_analogowa = analogRead(analog_pin);

  // if (wartosc_cyfrowa== LOW || wartosc_analogowa > 5500)
  if ( (wartosc_analogowa > neutral_value_max || wartosc_analogowa < neutral_value_min) && millis()-m >300)
  {
    if(wartosc_analogowa<50)
    {
      sensor_not_detected = true;
    }
    else
    {
      Serial.print("Wykryto magnes! counter: ");
      Serial.println(counter);
      Serial.print(" -Wartosc analogowa: ");
      Serial.println(wartosc_analogowa);
      counter++;
      m = millis();
      sensor_not_detected = false;
    }

  }

  Serial.println(wartosc_analogowa);
}