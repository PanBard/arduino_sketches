#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int analogPin = A3; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val = 0;  // variable to store the value read
int val_05_s = 0;
int val2 = 0;
long int k = 0;
long int k2 = millis();
long int k3 = millis();
int record_min = 500;
int record_max = 100;


void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();
}

void loop() {

  val = analogRead(analogPin);  // read the input pin
  testscrolltext();
  k=millis();
  if(k-k2>300)
  {
    k2=millis();
    val_05_s = analogRead(analogPin);
  }


   if(k-k3>100)
  {
    k3=millis();
    if(val > record_max){
      record_max=val;
    }

    if(val < record_min){
      record_min=val;
    }

  }


  // delay(200);
}


void testscrolltext() {
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println("analog read:");
  display.setTextSize(2); // Draw 2X-scale text
  display.setCursor(10, 30);
  display.println(val);
  display.setCursor(10, 50);
    if((val-val_05_s>100) || (val_05_s-val>100))
  {
    val2 = val_05_s;
     
  }
  display.println(val2);


  display.setTextSize(1); // Draw 2X-scale text
  display.setCursor(70, 30);
  display.println("max:");
  display.setCursor(100, 30);
  display.println(record_max);


  display.setCursor(70, 50);
  display.println("min:");
  display.setCursor(100, 50);
  display.println(record_min);


  display.display();      // Show initial text
}

