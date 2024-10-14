#include "OledStuff.h"
#include "analog.h"
void setup() 
{
  // analog_start();
  oled_start();
}

void loop()
{
  handle_analogRead();
}