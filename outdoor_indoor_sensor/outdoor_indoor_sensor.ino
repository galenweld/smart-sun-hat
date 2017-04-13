// Smart UV Sensing Hat project for Cornell INFO 4120
// Kevin Guo (kg344) and Galen Weld (gcw33)
// April 2017

#include <Wire.h>
#include "Adafruit_SI1145.h"
#include <Adafruit_NeoPixel.h>

// input thresholds
const int visThresh = 270;
const int uvThresh = 3;
const int tempThresh = 250;

// warning thresholds
const int highLight = 100;
const int highWarning = 200;

const int lowLight = -200;
const int lowWarning = -300;

int solarExposure;

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

  solarExposure = 0;
}

void loop() {
  //==============INPUTS==============
  float temp;
  float uvLight;
  float visLight;

  visLight = uv.readVisible();
  uvLight = uv.readUV();
  uvLight /= 100.0;
  temp = analogRead(tempSensor);
  
  if (visLight > visThresh) {
    solarExposure ++;
  }
  else if (visLight <= visThresh) {
    solarExposure --;
  }

  if (uvLight > uvThresh) {
    solarExposure ++;  
  }

  if (temp > tempThresh) {
    solarExposure ++;
  }
  
  //==============OUTPUTS==============
  Serial.print("UV: "); Serial.println(uvLight);
  Serial.print("Visible: "); Serial.println(visLight);
  Serial.print("Temp: "); Serial.println(temp);
  Serial.print("Solar Exposure: "); Serial.println(solarExposure);
  
  if (solarExposure < highWarning && solarExposure > lowWarning) {
    strip.setPixelColor(0, green);
    strip.setPixelColor(1, green);
    strip.show();

    noTone(buzzer);
  }

  if (solarExposure > highLight) {
    strip.setPixelColor(0, red);
    strip.setPixelColor(1, red);
    strip.show();

    noTone(buzzer);
  }

  if (solarExposure > highWarning) {
    tone(buzzer, 1000);
  }

  if (solarExposure < lowLight) {
    strip.setPixelColor(0, blue);
    strip.setPixelColor(1, blue);
    strip.show();

    noTone(buzzer);
  }

  if (solarExposure < lowWarning) {
    tone(buzzer, 250);
  }

  delay(100);
}
