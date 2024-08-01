#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// object of Adafruit_MPL3115A2 class
Adafruit_MPL3115A2 mpl;
// object of Adafruit_BNO055 class
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire1);

// variables for MPL3115A2 altimeter
float pressure = 0.0;
float altitude = 0.0;
float temperature = 0.0;
// elevation data for chicago
float mean_elevation = 182.02;  
float lowest_elevation = 176.00;
float highest_elevation = 205.00; 

// put function declarations here:

void setup() {
  Serial.begin(9600);
  
  while(!Serial){
    Serial.println("Communication error");
    while(1);
  }

  if (!mpl.begin()) {
    Serial.println("Could not find MPL3115A2");
    while(1);
  }

  if(!bno.begin()){
    Serial.print("Could not find BNO055");
    while(1);
  }
  
  //air pressure in Chicago -> 29.9 inHg = 1012.53 hPa
  mpl.setSeaPressure(1012.53);

  bno.setExtCrystalUse(true);
}


void loop() {
  // pressure = mpl.getPressure();
  // altitude = mpl.getAltitude();
  // temperature = mpl.getTemperature();

  // Serial.println("-----------------");
  // Serial.print("pressure = "); Serial.print(pressure); Serial.println(" hPa");
  // Serial.print("altitude = "); Serial.print(altitude - mean_elevation); Serial.println(" m");
  // Serial.print("temperature = "); Serial.print(temperature); Serial.println(" C");
  // Serial.println("");

  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  
  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");
}

// put function definitions here:
