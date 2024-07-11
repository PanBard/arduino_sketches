int counter = 0;
bool loop_state = false;
int green = 5;
int blue = 4;
int red = 6;
int analog_pin = 1;
int end_green = 10;
int end_blue = 20;
int max_red = 25;  // <-------------- max na bele

void setup() {
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(red,OUTPUT);
  clear_leds();
  //  Serial.begin(9600);
}

void loop() {

    digitalWrite(green, HIGH);
    delay(200);
    digitalWrite(green, LOW);
    delay(200);
    digitalWrite(green, HIGH);
    delay(200);
    digitalWrite(green, LOW);
    delay(200);

   while(counter == 0)
  {
    count();
    digitalWrite(green, HIGH);
  }

  while(counter <= end_green)
  {
    count();
    digitalWrite(green, HIGH);
  }

  clear_leds();

  while(counter > end_green && counter <= end_blue)
  {
    count();
    digitalWrite(blue, HIGH);
  }

  clear_leds();

  while(counter > end_blue && counter <= max_red)
  {
    count();
    digitalWrite(red, HIGH);
  }

  while(counter > max_red)
  {
    digitalWrite(red, HIGH); 
    delay(100);                      // wait for a second
    digitalWrite(red, LOW); 
    delay(100);  
  }
}


void clear_leds()
{
  digitalWrite(green, LOW); 
  digitalWrite(blue, LOW); 
  digitalWrite(red, LOW); 
}

void count()
{

  // Serial.print("counter: ");
  // Serial.println(counter);
  // Serial.print("analog: ");
  // Serial.println(analogRead(analog_pin));
  if(analogRead(analog_pin) > 1000)
  {
    counter ++;
    delay(300);
    clear_leds();
  }
      delay(100);
}




