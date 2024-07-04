#include<ADS1115_WE.h> 
#include<Wire.h>

// SDA nad SCL just the same as SDA and SCL in oled disply

#define I2C_ADDRESS 0x48
float voltage = 0.0;
ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);
 
void adc1115_start()
{
  // Serial.begin(9600);
   if(!adc.init()){
    // Serial.println("ADS1115 not connected!");
  }
  else
  {
      adc.setVoltageRange_mV(ADS1115_RANGE_6144); //comment line/change parameter to change range
  }
}



float readChannel(ADS1115_MUX channel) {
  float voltage = 0.0;
  adc.setCompareChannels(channel);
  adc.startSingleMeasurement();
  while(adc.isBusy()){}
  voltage = adc.getResult_mV(); // alternative: getResult_mV for Millivolt
  // Serial.println(voltage);
  return voltage;
}

float reat_value_adc1115()
{
  float voltage = 0.0;
  adc.setCompareChannels(ADS1115_COMP_0_GND);
  adc.startSingleMeasurement();
  while(adc.isBusy()){}
  voltage = adc.getResult_mV(); // alternative: getResult_mV for Millivolt
  return voltage;
}

float reat_V_value_adc1115()
{
  float voltage = 0.0;
  adc.setCompareChannels(ADS1115_COMP_0_GND);
  adc.startSingleMeasurement();
  while(adc.isBusy()){}
  voltage = adc.getResult_V(); // alternative: getResult_mV for Millivolt
  return voltage;
}

float reat_raw_value_adc1115()
{
  float voltage = 0.0;
  adc.setCompareChannels(ADS1115_COMP_0_GND);
  adc.startSingleMeasurement();
  while(adc.isBusy()){}
  voltage = adc.getRawResult(); // alternative: getResult_mV for Millivolt
  return voltage;
}
