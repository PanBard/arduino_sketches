#include "OledStuff.h"
#include "analog.h"

void setup() 
{
  oled_start();
  analog_start();
}

void loop()
{
  handle_analogRead();
}

