
//for temperature
#include <SimpleDHT.h>

int periodMilis = 100;

int pinTemperature = 2;
int redpin = 9; //select the pin for the red LED
int greenpin = 10;// select the pin for the green LED
int bluepin = 11; // select the pin for the  blue LED
int lightSensorPin = A0; // select the pin for the  blue LED
int moistureSensorPin = A1; // select the pin for the  blue LED
int relayLightPin = 4;
int relayWaterPin = 5;

#include "temperature.h"
Temperature modTemp;

#include "rgb.h"
RGB rgb;

#include "LightSensor.h"
LightSensor lightSensor;

#include "MoistureSensor.h"
MoistureSensor moistureSensor;

#include "Relay.h"
Relay relayLight;
Relay relayWater;

#include "Hub.h"
Hub hub;

void setup() {
  Serial.begin(9600);
  rgb.init();
  lightSensor.init(lightSensorPin);
  moistureSensor.init(moistureSensorPin);

  relayLight.init(relayLightPin);
  relayWater.init(relayWaterPin);
  hub.init();

  //water(1.0);
  //hub.launchProcess(new ProcessWater(2.0));
  hub.launchProcess(new ProcessLight(8.0));
}

void loop() {
  hub.doStep(periodMilis);

  /*modTemp.getValue();
  int lightVal = lightSensor.getValue();
  int moistureVal = moistureSensor.getValue();
  rgb.setColor(moistureVal / 4, 0,0);*/


  // DHT11 sampling rate is 1HZ.
  delay(periodMilis);
}

void water(float time) {
  rgb.setColor(0, 0, 128);
  relayWater.turnOn();
  delay(time * 1000.0);
  relayWater.turnOff();
  rgb.setColor(0, 0, 0);
}





