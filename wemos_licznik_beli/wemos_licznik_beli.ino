#include "HallaStaff.h"
#include "OledStuff.h"


void setup() 
{
  Serial.begin(9600);
  oled_start(); //OLED setup 
  // updateScreen();
  delay(1000);
  alert();
}

void loop() 
{
// oled_display("elo");
updateScreen();
halotron_run();
}




