
//for temperature
#include <SimpleDHT.h>

int periodMilis = 2000;

int pinTemperature = 2;
int redpin = 10; //select the pin for the red LED
int greenpin = 11;// select the pin for the green LED
int bluepin = 9; // select the pin for the  blue LED
int lightSensorPin = A0; // select the pin for the  blue LED
int moistureSensorPin = A1; // select the pin for the  blue LED
int relayLightPin = 4;
int relayWaterPin = 5;

//model
int minMoisture = 200;
int minLight = 200;

//data
int moistureVal;
int lightVal;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

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

  //check();

  //water(1.0);
  //hub.launchProcess(new ProcessMonitor());
  //hub.launchProcess(new ProcessWater(4.0));
  //hub.launchProcess(new ProcessLight(8.0));

  //Process* p = new ProcessFade(2, 5);
  //p->attachedProcess = new ProcessFade(4.0);
  //hub.launchProcess(p);
}

void loop() {

  // print the string when a newline arrives:

  hub.doStep(periodMilis);

  modTemp.getValue();
  lightVal = lightSensor.getValue();
  moistureVal = moistureSensor.getValue();

  if (moistureVal < minMoisture) {
    rgb.setBlue(128);
  }
  else {
    rgb.setBlue(0);
  }

  if (lightVal < minLight) {
    rgb.setRed(128);
  }
  else {
    rgb.setRed(0);
  }


  Serial.print((int)modTemp.temperature); 
  Serial.print(";");
  Serial.print((int)modTemp.humidity); 
  Serial.print(";");
  Serial.print(moistureVal); 
  Serial.print(";");
  Serial.print(lightVal); 
  Serial.println();
  // DHT11 sampling rate is 1HZ.
  delay(periodMilis);
}

void OnCommandReceive(String input) {
  if (inputString == "check") {
      Serial.println("#laucnhing check");
      check();
    }
    else if (inputString == "water") {
      Serial.println("#watering for 10 sec");
      water(10);
    }
    else {
      Serial.println("#cmd undefinded : " + inputString);
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();

    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
       OnCommandReceive(inputString);
    }
    else {
      // add it to the inputString:
      inputString += inChar; 
    }
  }
}

void water(float time) {
  rgb.setColor(0, 0, 128);
  relayWater.turnOn();
  delay(time * 1000.0);
  relayWater.turnOff();
  rgb.setColor(0, 0, 0);
}

void check() {
  float dt = 1000;
  rgb.setColor(255, 0, 0);
  delay(dt);
  rgb.setColor(0, 255, 0);
  delay(dt);
  rgb.setColor(0, 0, 255);
  delay(dt);
  rgb.setColor(0, 0, 0);
  delay(dt);

  rgb.setColor(0, 0, 255);
  relayWater.turnOn();
  delay(dt);

  rgb.setColor(0, 0, 0);
  relayWater.turnOff();
  delay(dt);

  rgb.setColor(255, 255, 0);
  relayLight.turnOn();
  delay(dt);

  rgb.setColor(0, 0, 0);
  relayLight.turnOff();
  delay(dt);
}









