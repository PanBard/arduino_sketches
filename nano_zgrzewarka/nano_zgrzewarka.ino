const int BUTTON_PIN = 2; 
const int TRANZYSTOR_PIN = 3; 
int button_state; 


void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(TRANZYSTOR_PIN, OUTPUT);
    digitalWrite(TRANZYSTOR_PIN, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() 
{
    button_state = digitalRead(BUTTON_PIN);
    if( button_state == LOW)
    {
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(30);                      // wait for a second
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
      // delay(1000);
      digitalWrite(TRANZYSTOR_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(1000);                      // wait for a second
      digitalWrite(TRANZYSTOR_PIN, LOW);   // turn the LED off by making the voltage LOW
      delay(1000);
    }
}
