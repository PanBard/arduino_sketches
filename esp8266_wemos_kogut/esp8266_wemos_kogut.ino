int pin_1 = 3;//  GIO3 (RX on wemos) ...
int pin_2 = 5;
int pin_3 = 4;
int pin_4 = 0;
int pin_5 = 2;
int interval = 50;

void setup() {
  // put your setup code here, to run once:
pinMode(BUILTIN_LED, OUTPUT);
pinMode(pin_1, OUTPUT); 
pinMode(pin_2, OUTPUT); 
pinMode(pin_3, OUTPUT); 
pinMode(pin_4, OUTPUT); 
pinMode(pin_5, OUTPUT); 

digitalWrite(BUILTIN_LED, HIGH);
}

void loop() {

light_on(pin_1,interval);
light_on(pin_2,interval);
light_on(pin_3,interval);
light_on(pin_4,interval);
light_on(pin_5,interval);

}

void light_on(int pin, int time)
{
  digitalWrite(pin, HIGH);//on
  delay(time);
  digitalWrite(pin, LOW); //off
  delay(time);
}
