#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> // by Adafruit
#include <Wire.h>  //for custom sda, scl define

Adafruit_SSD1306 display(128, 32, &Wire, -1);  // On wemos:   D2(SDA),  D1(SCL); VCC=3.3v;
long time_alert_1 = millis();
long time_alert_2 = millis();
int alert_interval_1 = 1000;
int alert_interval_2 = 2000;

void oled_display(String message) {
  display.clearDisplay();                           // Clear display buffer
  display.setTextSize(1);                           // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, 1);
  display.println(message);
  display.display();  // Update screen
}

void alert()
{
   if(millis() - time_alert_1 > alert_interval_1)
  {
    time_alert_1 = millis();
    display.clearDisplay(); // Clear display buffer
    display.display(); // Update screen
  }
  if(millis() - time_alert_2 > alert_interval_2)
  {
    time_alert_2 = millis();
    display.drawLine(0, 32, 128,32, SSD1306_WHITE); // (x1,y1,x2,y2,color)
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(27, 10);
    display.println(F("WYWAL"));
    display.display(); // Update screen
  }
 
  // display.clearDisplay(); // Clear display buffer
  // display.display(); // Update screen
  // delay(1000);
  // display.drawLine(0, 32, 128,32, SSD1306_WHITE); // (x1,y1,x2,y2,color)
  // display.setTextSize(2); // Draw 2X-scale text
  // display.setTextColor(SSD1306_WHITE);
  // display.setCursor(27, 10);
  // display.println(F("WYWAL"));
  // display.display(); // Update screen
  // delay(1000);
}

void updateScreen()
{
  if(max_turn_number>counter)
  {

  display.clearDisplay(); // Clear display buffer
  display.drawLine(0, 32, 128,32, SSD1306_WHITE); // (x1,y1,x2,y2,color)
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, 5);
  display.println(F("OBROTY:"));
  display.setCursor(45, 5);
  display.println(counter);
  display.drawRect(1,15,127,17,SSD1306_WHITE); // drawRect(x,y,width, height)
  
  
      int e = 0;
    int er = 128/max_turn_number;

    for (int i = 0; i <= counter; i++) 
    {
      e=e+er;
       display.fillRect(3, 17, e, 13, SSD1306_WHITE);
    }
  }
  else
  {
    alert();
  }

  display.display(); // Update screen
}




void oled_start() {
  // Wire.begin(I2C_SDA, I2C_SCL);                      //Wire.begin(I2C_SDA, I2C_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  //See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Don't proceed, loop forever
  }
  // Serial.println("oled display status: ok");
  display.clearDisplay();
}