
int c = 0;
long m = millis();
int analog_pin = 12;
int neutral_value_max = 5370;
int neutral_value_min = 5480;
void setup() 
{
 Serial.begin(9600);

//  pinMode(3,INPUT);

}

void loop() 
{
  int wartosc_cyfrowa = 0; 
  int wartosc_analogowa = 0;

  // wartosc_cyfrowa = digitalRead(3);
  wartosc_analogowa = analogRead(analog_pin);

  // if (wartosc_cyfrowa== LOW || wartosc_analogowa > 5500)
   if ( (wartosc_analogowa < neutral_value_max || wartosc_analogowa > neutral_value_min) && millis()-m >300)
  {
    // srednio 5420-5430 w spoczynku
    Serial.println("Wykryto magnes!");
    Serial.print(c);
    Serial.print(" -Wartosc analogowa: ");
    Serial.println(wartosc_analogowa);
    c++;
    m = millis();
  }

Serial.println(wartosc_analogowa);

  delay(100);
  

}