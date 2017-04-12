// Smart UV Sensing Hat project for Cornell INFO 4120
// Kevin Guo (kg344) and Galen Weld (gcw33)
// April 2017

#include <Wire.h>
#include "Adafruit_SI1145.h"
#include <Adafruit_NeoPixel.h>

int temp;
float visLight;
float uvLight;

//pins
const int buzzer = 6; //buzzer to pin 6
const int photoResistor = 9; //photoresistor to pin 9
const int led = 10; //led to pin 10
const int tempSensor = 12; //temperature sensor to pin 12

Adafruit_SI1145 uv = Adafruit_SI1145();
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, led, NEO_GRB + NEO_KHZ800);

  uint32_t red = strip.Color(255, 0, 0);
  uint32_t green = strip.Color(0, 255, 255);
  uint32_t blue = strip.Color(0, 0, 255);
  uint32_t purple = strip.Color(255, 0, 255);
  uint32_t white = strip.Color(255, 255, 255);

void setup() {
  //Begins serial communcation with temperature sensor, photoresistor
  Serial.begin(9600);

  //led
  pinMode(led, OUTPUT);
  //buzzer
  pinMode(buzzer, OUTPUT);

  //uv sensor
  if (! uv.begin()) {
    Serial.println("Didn't find Si1145");
    while (1);
  }

  //leds
  strip.begin();
  strip.show();
}

void loop() {
  //==============INPUTS==============
  //photo resistor
  visLight = analogRead(photoResistor);

  //uv sensor
  uvLight = uv.readUV();
  uvLight /= 100.0;

  //temperature sensor
  temp = analogRead(tempSensorPin);
  degreesC = sensorValue/2.046 - 50.0;
  
  //==============OUTPUTS==============
  //buzzer
  tone(buzzer, 1000);
  delay(1000); //waits a second

  //led output for the first led, will indicate 
  if(visLight >= ){
  
  }
  else if(visLight >= ){
    
  }
  else{
  
  }
  
  //led output for 
  if(uvLight >= ){
    strip.setPixelColor()
  }
  else if(uvLight >=){
  
  }
  else{
  
  }
  
  //analogWrite(led, analogRead(photoResistor)/4);
  //delay(1000); //waits a second

}
