// Smart UV Sensing Hat project for Cornell INFO 4120
// Kevin Guo (kg344) and Galen Weld (gcw33)
// April 2017

#include <Wire.h>
#include "Adafruit_SI1145.h"
#include <Adafruit_NeoPixel.h>

float temp;
float uvLight;
float visLight;

//pins
const int buzzer = 6; //buzzer to pin 6
const int photoResistor = 12; //photoresistor to pin 9
const int led = 10; //led to pin 10
const int tempSensor = 9; //temperature sensor to pin 12

Adafruit_SI1145 uv = Adafruit_SI1145();
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, led, NEO_GRB + NEO_KHZ800);

uint32_t red = strip.Color(255, 0, 0);
uint32_t purple = strip.Color(255, 0, 255);
uint32_t blue = strip.Color(0, 0, 255);

uint32_t green = strip.Color(0, 255, 0);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t orange = strip.Color(255, 144, 0);
  
void setup() {
  //Begins serial communcation with temperature sensor, photoresistor
  Serial.begin(9600);
  
  //photoresistor
  pinMode(photoResistor, INPUT);
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
  //visLight = analogRead(photoResistor);
  visLight = uv.readVisible();
  visLight /= 4;
  //uv sensor
  uvLight = uv.readUV();
  uvLight /= 100.0;

  //temperature sensor
  //temp = analogRead(tempSensor);
  float reading = analogRead(tempSensor);
  temp = reading/2.046 - 50.0;
  
  //==============OUTPUTS==============
  Serial.print("UV: "); Serial.println(uvLight);
  Serial.print("Visible: "); Serial.println(visLight);
  Serial.print("Temp: "); Serial.println(temp);
  
  if(uvLight >= 5){
    tone(buzzer, 1000);
    delay(1000);
    noTone(buzzer);
    delay(1000);
  }
  else if(uvLight >= 3){
    tone(buzzer, 500);
    delay(500);
    noTone(buzzer);
    delay(2000);
  }
  else{
    tone(buzzer, 250);
    delay(250);
    noTone(buzzer);
    delay(4000);
  }
  //led output for the first led, will indicate temperature
  //from blue at low temps to red at hot temps
  if(temp >= 75){
    strip.setPixelColor(0, red);
    strip.show();
  }
  else if(temp >= 60){
    strip.setPixelColor(0, green);
    strip.show();
  }
  else{
    strip.setPixelColor(0, blue);
    strip.show();
  }
  
  //led output for the second led, will indicate visible light
  //from green at low light to orange at high light
  if(visLight >= 90){
    strip.setPixelColor(1, red);
    strip.show();
  }
  else if (visLight >= 60){
    strip.setPixelColor(1, green);
    strip.show();
  }
  else{
    strip.setPixelColor(1, purple);
    strip.show();
  }
  delay(100);
}
