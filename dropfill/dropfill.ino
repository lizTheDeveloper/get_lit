#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 28

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 8
#define CLOCK_PIN 13
# 

// Define the array of leds
CRGB leds[NUM_LEDS];

//contains the rain fill level
static uint8_t countHolder = NUM_LEDS; 
static uint8_t hueInit = 0;
static uint8_t hueAlt = 20;


void setup() { 
  Serial.begin(57600);
  Serial.println("resetting");
  // LEDs are at addresses //36 - 52, step 2
  LEDS.addLeds<WS2812,36,RGB>(leds,NUM_LEDS);
  LEDS.addLeds<WS2812,38,RGB>(leds,NUM_LEDS);
  LEDS.addLeds<WS2812,40,RGB>(leds,NUM_LEDS);
  LEDS.addLeds<WS2812,42,RGB>(leds,NUM_LEDS);
  LEDS.addLeds<WS2812,44,RGB>(leds,NUM_LEDS);
  LEDS.addLeds<WS2812,46,RGB>(leds,NUM_LEDS);
  LEDS.addLeds<WS2812,48,RGB>(leds,NUM_LEDS);
  LEDS.addLeds<WS2812,50,RGB>(leds,NUM_LEDS);
  LEDS.addLeds<WS2812,52,RGB>(leds,NUM_LEDS);
  
  LEDS.setBrightness(84);
}

void fadeall() { 
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(250); 
  } 
}



void loop() { 
  //then slide down an LED until you get to the highest filled LED
  for (int fall = 0, rain = 0; fall < countHolder; fall++) {
    leds[fall] = CHSV(hueInit, 255, 255);
    if (rain < (fall - 2) && rain < countHolder) {
      leds[rain] = CHSV(0, 0, 0);
      rain++;
    }
    FastLED.show();
    delay(1);
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    if (i > countHolder) {
      leds[i] = CHSV(hueAlt, 255, 255);  
    }
    FastLED.show(); 
    fadeall();
    delay(2);
  }
  countHolder--;
  if (countHolder == 0) {
    countHolder = NUM_LEDS;
    hueInit += 10;
    hueAlt += 10;
    hueInit = hueInit % 255;
    hueAlt = hueAlt % 255;
  }
}
