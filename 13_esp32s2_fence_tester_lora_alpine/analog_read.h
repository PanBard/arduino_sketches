#define analog_pin_fotorezystor 3 //analogpin x pin 3
#define MESSAGE_LENGTH 10 // max message lenght
char message[MESSAGE_LENGTH];
long int current_time = 0;
long int last_send_time = millis();
int record_min = 8000;
int record_max = 0;
int foto_value = 0; // variable to store the analog value read
int interval_in_miliseconds = 10000; // <----------------------------------- set up a interval between lora packet sending

void run_all() {
  current_time=millis();
  if(current_time-last_send_time>interval_in_miliseconds)
  {
    snprintf(message, MESSAGE_LENGTH, "%d", record_max-record_min); //convert int to char
    lora_send_message(message);
    last_send_time=millis();
    record_max=0;
    record_min=8000;
  }
  foto_value = analogRead(analog_pin_fotorezystor);
  if(foto_value > record_max)
  {
    record_max=foto_value;
  }
  if(foto_value < record_min)
  {
    record_min=foto_value;
  }
}
