// Smart UV Sensing Hat project for Cornell INFO 4120
// Kevin Guo (kg344) and Galen Weld (gcw33)
// April 2017

#include <Wire.h>
#include "Adafruit_SI1145.h"
#include <Adafruit_NeoPixel.h>

float temp;
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
uint32_t purple = strip.Color(255, 0, 255);
uint32_t blue = strip.Color(0, 0, 255);

uint32_t green = strip.Color(0, 255, 0);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t orange = strip.Color(255, 144, 0);
  
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
  temp = analogRead(tempSensor);
  temp = temp/2.046 - 50.0;
  
  //==============OUTPUTS==============
  //buzzer
  if(uvLight >= 5){
    tone(buzzer, 1000);
    delay(3000);
  }
  else if(uvLight >= 2){
    tone(buzzer, 1000);
    delay(1500);
  }
  else{
    tone(buzzer, 1000);
    delay(750);
  }
  noTone(buzzer);
  delay(1000);
  
  //led output for the first led, will indicate temperature
  //from blue at low temps to red at hot temps
  if(temp >= 27){
    strip.setPixelColor(0, red);
    strip.show();
  }
  else if(temp >= 22){
    strip.setPixelColor(0, purple);
    strip.show();
  }
  else{
    strip.setPixelColor(0, blue);
    strip.show();
  }
  
  //led output for the second led, will indicate visible light
  //from green at low light to orange at high light
 if(visLight >= 220){
    strip.setPixelColor(1, orange);
    strip.show();
  }
  else if(visLight >= 200){
    strip.setPixelColor(1, yellow);
    strip.show();
  }
  else{
    strip.setPixelColor(1, green);
    strip.show();
  }
  delay(10);
}
