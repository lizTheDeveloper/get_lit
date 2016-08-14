#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 28

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 8
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

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
  static uint8_t hue = 0;
  static uint8_t flashHolder = 0;
  static uint8_t hueRange = 10;
  Serial.print("x");
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  Serial.print("x");

  //crazy flash
  // log g and b to the r gives you fire 
  
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(flashHolder+=10, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }

  // Now go in the other direction.  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  
//  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
//    leds[i] = CHSV(hue, 255, 255);
//    FastLED.show();
//    delay(10);
//  }
//  hue = hue + 10 % 256;
}
