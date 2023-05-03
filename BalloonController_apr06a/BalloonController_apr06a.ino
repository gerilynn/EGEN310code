#include "arduino_secrets.h"
#include <DFRobot_BME680_I2C.h>
#include <Wire.h>
/* 
  
  float airQuality;
  float pressure;
  CloudTemperatureSensor temperature;
  int hall;
  bool fan;
*/

#include "thingProperties.h"

DFRobot_BME680_I2C bme(0x77);
int FAN = 18;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(500); 
  uint8_t result = 1;
  result = bme.begin();
  while(result != 0){
    result=bme.begin();
    if(result !=0){
      Serial.println("BME sensor not found");
      delay(2000);
    }
  }
  Serial.println("BME connected successfully");

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors). Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  pinMode(FAN, OUTPUT);
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  bme.startConvert();
  bme.update();
  temperature = bme.readTemperature()/100;
  pressure = bme.readPressure();
  hall = hallRead();
  airQuality = bme.readGasResistance();
  
  Serial.print("Pressure: ");
  Serial.println(pressure);
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" C");
  Serial.print("Magnetic Field: ");
  Serial.println(hall);
  Serial.print("Air Quality: ");
  Serial.println(airQuality);
  Serial.println("");
  delay(1000);
}

/*
  Since Fan is READ_WRITE variable, onFanChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onFanChange()  {
  Serial.println("Fan change registered");
  if(fan){
    digitalWrite(FAN, HIGH);
  }else{
    digitalWrite(FAN, LOW);
  }
}









