#define analog_pin_general 3 //analogpin x pin 3
#define analog_pin_switch 5 //analogpin x pin 3
#define switch_pin 9 //analogpin x pin 3
#define red_led_pin 11 //analogpin x pin 3
#define green_led_pin 12 //analogpin x pin 3

// int analog_value_general;
int analog_value_switch;
float general_voltage_factor = 6662.0; //  42.0 V ---> 6662 analog value
float general_voltage_ref = 42.0; //  42.0 V ---> 6662 analog value
// float general_voltage;
float switch_voltage;
bool calculate_charge_time = false;
bool charge_end = false;

long int charge_start_time = 0;
long int charge_time = 0;
long int last_update_time_for_max_value = millis();
long int last_update_time_for_current_value = millis();

float charge_baterry_voltage_level_detection = 25.0; // min 25v to turn on charger
float charge_baterry_voltage_level_end = 41.4; // max 41.4v to turn off charger

int values[20];
int average_values[10];

void analog_start()
{
  pinMode(switch_pin, OUTPUT);
  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  digitalWrite(switch_pin, HIGH);
  digitalWrite(red_led_pin, LOW);
  digitalWrite(green_led_pin, LOW);
}

int analog_average_calculating(int choosen_pin)
{
  for (int i = 0; i < 20; i++) 
  {
		values[i] = analogRead(choosen_pin);
    delay(10);
  }
  

 // Sort the array (Bubble Sort for simplicity)
  for (int i = 0; i < 19; i++) 
  {
    for (int j = 0; j < 19 - i; j++) 
    {
      if (values[j] > values[j + 1]) 
      {
        int temp = values[j];
        values[j] = values[j + 1];
        values[j + 1] = temp;
      }
    }
  }

  // Discard the 4 highest and 4 lowest values
  int sum = 0;
  for (int i = 4; i < 16; i++) { // Only sum values from index 4 to 15
    sum += values[i];
  }

  //Calculate the average of the remaining 12 values
  int average = sum / 12;

  return average;
}




int analog_get_average(int choosen_pin)
{
  for (int i = 0; i < 10; i++) 
  {
		average_values[i] = analog_average_calculating(choosen_pin);
  }
  

 // Sort the array (Bubble Sort for simplicity)
  for (int i = 0; i < 9; i++) 
  {
    for (int j = 0; j < 9 - i; j++) 
    {
      if (average_values[j] > average_values[j + 1]) 
      {
        int temp = average_values[j];
        average_values[j] = average_values[j + 1];
        average_values[j + 1] = temp;
      }
    }
  }

  // Discard the 2 highest and 2 lowest values
  int sum = 0;
  for (int i = 2; i < 8; i++) { // Only sum values from index 4 to 15
    sum += average_values[i];
  }

  //Calculate the average of the remaining 6 values
  int average = sum / 6;

  return average;
}

void handle_analogRead() 
{
  //zmiana na 1 probnik
  analog_value_switch = analog_get_average(analog_pin_switch);
  switch_voltage = (analog_value_switch*general_voltage_ref)/general_voltage_factor;
  oled_display_content(switch_voltage, charge_baterry_voltage_level_detection,charge_baterry_voltage_level_end, (charge_time - charge_start_time)/1000, charge_end);

  if((switch_voltage >=  charge_baterry_voltage_level_detection) && (switch_voltage <  charge_baterry_voltage_level_end) && (charge_end == false))
  {
    digitalWrite(switch_pin,LOW);
    digitalWrite(green_led_pin, LOW);
    digitalWrite(red_led_pin, HIGH);
    if(charge_start_time == 0 || calculate_charge_time) 
    {
      charge_start_time = millis();
      calculate_charge_time = false;
    }
    charge_time = millis();
  }
  else if(switch_voltage > charge_baterry_voltage_level_end && charge_end == false)
  {
    charge_end = true;
  }
  else
  {
    digitalWrite(switch_pin,HIGH);
    digitalWrite(red_led_pin, LOW);
    digitalWrite(green_led_pin, HIGH);
    calculate_charge_time = true;
  }



}

