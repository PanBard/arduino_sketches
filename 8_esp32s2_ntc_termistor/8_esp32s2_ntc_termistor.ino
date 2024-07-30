const int analogPin = 12; // Analog pin connected to the NTC thermistor
//R1 = termistor
const int R = 22000; // Resistor value in ohms
const int V_in = 3.3;
void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(analogPin);
  Serial.print("sensorValue:");
  Serial.print(sensorValue);

  float V_out = (sensorValue*3.3)/8191;
    Serial.print("V_out:");
    Serial.print(V_out);

  // Convert analog reading to resistance R1 = (R*V_out) / (V_in-V_out)
  // float resistance = (R*V_out) / (V_in-V_out);
  float resistance =  R*(V_in-V_out)/V_out;
  // float resistance = ( ( ((sensorValue*3.3)/8192) / (3.3*resistorValue) )- resistorValue );
  Serial.print("resistance:");
  Serial.print(resistance);


  // Use the Steinhart-Hart equation to convert resistance to temperature in Celsius
float temperature = (25*resistance)/10000.0;
  // float temperature = log(resistance / 10000.0) / 3950.0 + 1.0 / (25 + 273.15);

  // Convert temperature to Fahrenheit if desired
  float temperatureF = (temperature * 9.0 / 5.0) + 32.0;

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | ");
  Serial.print(temperatureF);
  Serial.println(" °F");

  delay(1000); // Delay for one second before reading again
}