#define analog_pin 4 //analogpin x pin 3
#define analog_pin_fotorezystor 6 //analogpin x pin 3

int val = 0;  // variable to store the value read
int val_05_s = 0;
int val2 = 0;
long int k = 0;
long int k2 = millis();
long int k3 = millis();
int record_min = 500;
int record_max = 100;
int foto_value = 0;

void run_all() {
//  val = analogRead(analog_pin);  // read the input pin
  k=millis();
  if(k-k2>5000)
  {
    lora_send_message(String(record_max-record_min));
    k2=millis();
    val_05_s = analogRead(analog_pin);
    record_max=0;
    record_min=8000;
  }
    foto_value = analogRead(analog_pin_fotorezystor);
  //  if(k-k3>100)
  // {
  //   k3=millis();
  //   foto_value = analogRead(analog_pin_fotorezystor);
  // }

    if(foto_value > record_max){
      record_max=foto_value;
    }

    if(foto_value < record_min){
      record_min=foto_value;
    }
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println("analog read:");
  display.setCursor(100, 0);
  display.println(record_max-record_min);
  display.setTextSize(2); // Draw 2X-scale text
  display.setCursor(10, 30);
  display.println(record_max-record_min);
  display.setTextSize(1); // Draw 2X-scale text
  display.setCursor(10, 50);
  display.println("foto:");
    if((val-val_05_s>100) || (val_05_s-val>100))
  {
    val2 = val_05_s;
  }
  display.setCursor(40, 50);
  display.println(foto_value);
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
