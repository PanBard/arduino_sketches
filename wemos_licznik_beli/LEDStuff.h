
int green = 16; //D0
int blue = 12; //D5
int red = 14; //D6

//1-d5
//2-d0
//3-d6


int end_green = 10;
int end_blue = 20;

void start_LED()
{   digitalWrite(green, LOW); 
    digitalWrite(blue, LOW); 
    digitalWrite(red, LOW);

   digitalWrite(green, HIGH);
    delay(100);
    digitalWrite(green, LOW);
    delay(100);
    digitalWrite(green, HIGH);
    delay(100);
    digitalWrite(green, LOW);
    delay(100);
}

void blue_LED_signal()
{   digitalWrite(green, LOW); 
    digitalWrite(blue, LOW); 
    digitalWrite(red, LOW);

   digitalWrite(blue, HIGH);
    delay(100);
    digitalWrite(blue, LOW);
    delay(100);
    digitalWrite(blue, HIGH);
    delay(100);
    digitalWrite(blue, LOW);
    delay(100);
}

void run_leds_show() {
  if(sensor_not_detected)
  {
    digitalWrite(green, LOW); 
    digitalWrite(blue, LOW); 
    digitalWrite(red, LOW);
  }
  else
  {
        if(counter == 0)
  {
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
  }

  if(counter > 0 && counter < max_turn_number)
  {
    digitalWrite(green, LOW);
    digitalWrite(blue, HIGH);
    digitalWrite(red, LOW);
  }

  if(counter >=  max_turn_number)
  {
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(red, HIGH);
    delay(200);
    digitalWrite(red, LOW);
    delay(200);

  }
  }
}




void LED_start() 
{
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(red,OUTPUT);
 
  digitalWrite(green, LOW); 
  digitalWrite(blue, LOW); 
  digitalWrite(red, LOW);
}




