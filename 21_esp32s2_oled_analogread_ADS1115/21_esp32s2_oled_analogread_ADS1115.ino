#include "OledStuff.h"
#include "ads1115_stuff.h"
#include "analog.h"

void setup() 
{
  oled_start();
  adc1115_start();
  analog_start();
}

void loop()
{
  handle_analogRead();
}

