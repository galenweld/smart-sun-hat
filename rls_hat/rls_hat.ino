#include <Adafruit_NeoPixel.h>

#define PIN 10
const int delay_time = 200;
const int buzzer_pin = 6;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);

uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 255);
uint32_t blue = strip.Color(0, 0, 255);
    

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinMode(buzzer_pin, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  strip.setPixelColor(0, red);
  strip.setPixelColor(1, blue);
  strip.show();
  tone(buzzer_pin, 1000);
  delay(delay_time);
  
  strip.setPixelColor(0, blue);
  strip.setPixelColor(1, red);
  strip.show();
  tone(buzzer_pin, 8000);
  delay(delay_time);
}
