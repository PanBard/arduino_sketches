#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> // by Adafruit
#include <Wire.h>  //for custom sda, scl define

Adafruit_SSD1306 display(128, 32, &Wire, -1);  // On wemos:   D2(SDA),  D1(SCL); VCC=3.3v;
bool new_custom_turn_value_state = false;


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
    display.clearDisplay(); // Clear display buffer
    display.drawLine(0, 32, 128,32, SSD1306_WHITE); // (x1,y1,x2,y2,color)
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(27, 10);
    display.println(F("WYWALAJ"));
    display.display(); // Update screen
}

void display_start_screen()
{
    display.clearDisplay(); // Clear display buffer
    display.display();
    display.drawLine(0, 32, 128,32, SSD1306_WHITE); // (x1,y1,x2,y2,color)
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2); // Draw 2X-scale text
    display.setCursor(1, 15);
    display.println(counter);
    display.setCursor(104, 16);
    display.println(max_turn_number);
    display.drawRect(25,15,77,17,SSD1306_WHITE); // drawRect(x,y,width, height)
    display.display(); // Update screen
}



void updateScreen()
{
  if(counter != counter_job )
  {
      if(max_turn_number>counter)
    {
      display.clearDisplay(); // Clear display buffer
      display.drawLine(0, 32, 128,32, SSD1306_WHITE); // (x1,y1,x2,y2,color)
      display.setTextSize(1); // Draw 2X-scale text
      display.setTextColor(SSD1306_WHITE);

      display.setTextSize(2); // Draw 2X-scale text
      display.setCursor(1, 16);
      display.println(counter);
      display.setCursor(104, 16);
      display.println(max_turn_number);

      display.drawRect(25,15,77,17,SSD1306_WHITE); // drawRect(x,y,width, height)
      
    if(new_custom_turn_value_state)
    { 
      display.setTextSize(1); // Draw 2X-scale text
      display.setCursor(98, 5);
      display.println(">");
      display.drawLine(25, 8, 97, 8, SSD1306_WHITE);
      // display.setCursor(90, 5);
      // display.println(F("max:"));
      // display.setCursor(110, 5);
      // display.println(max_turn_number);
    }
      
        int e = 0;
        int er = 77/max_turn_number;

        for (int i = 0; i <= counter; i++) 
        {
          e=e+er;
          display.fillRect(28, 17, e, 13, SSD1306_WHITE);
        }
      }
      else
      {
        alert();
      }
      display.display(); // Update screen


    counter_job = counter;
  }

  if(sensor_not_detected)
  {
    display.clearDisplay();
    display.setTextSize(1); // Draw 2X-scale text
    display.setCursor(1, 5);
    display.println("Nie wykryto czujnika!");
    display.setCursor(10, 16);
    display.println("Podlacz czujnik.");
    display.display(); // Update screen
  }
 
}




void oled_start() {
  // Wire.begin(I2C_SDA, I2C_SCL);                      //Wire.begin(I2C_SDA, I2C_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  //See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Don't proceed, loop forever
  }
  // Serial.println("oled display status: ok");
  display.clearDisplay();
  display_start_screen();
}