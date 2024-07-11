
void blink() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(20);                         // wait 
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
}


int counter = 0;
long m = millis();
int analog_pin = 12;
int neutral_value_max = 5300;
int neutral_value_min = 5500;

void halotron_run() 
{
  int wartosc_cyfrowa = 0; 
  int wartosc_analogowa = 0;

  // wartosc_cyfrowa = digitalRead(3);
  wartosc_analogowa = analogRead(analog_pin);

  // if (wartosc_cyfrowa== LOW || wartosc_analogowa > 5500)
   if ( (wartosc_analogowa < neutral_value_max || wartosc_analogowa > neutral_value_min) && millis()-m >300)
  {
    // srednio 5420-5430 w spoczynku
    Serial.print("Wykryto magnes! counter: ");
    Serial.println(counter);
    Serial.print(" -Wartosc analogowa: ");
    Serial.println(wartosc_analogowa);
    counter++;
    m = millis();
  }

Serial.println(wartosc_analogowa);

  delay(100);
  
}