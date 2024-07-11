#include "HallaStaff.h"
#include "OledStuff.h"
#include "ButtonStuff.h"
#include "LEDStuff.h"
#include "OneFunctionToRuleThemAll.h"
void setup() 
{
  // Serial.begin(9600);
  oled_start(); //OLED setup 
  button_start();
  LED_start(); 
}

void loop() 
{
  main_function();
}




