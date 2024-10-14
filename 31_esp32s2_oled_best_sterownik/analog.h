#define analog_pin_voltage 5 //analogpin x pin 3
#define switch_pin 9 //analogpin x pin 3

int analog_value_voltage;
float voltage_factor = 6662.0; //  42.0 V ---> 6662 analog value
float voltage_ref = 42.0; //  42.0 V ---> 6662 analog value

float voltage;

int values[20];
int average_values[10];

// void analog_start()
// {
//   pinMode(switch_pin, OUTPUT);
//   pinMode(red_led_pin, OUTPUT);
//   pinMode(green_led_pin, OUTPUT);
//   digitalWrite(switch_pin, HIGH);
//   digitalWrite(red_led_pin, LOW);
//   digitalWrite(green_led_pin, LOW);
// }
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
  analog_value_voltage = analog_get_average(analog_pin_voltage);
  voltage = (analog_value_voltage*voltage_ref)/voltage_factor;
  oled_display_content(voltage);
  
}

