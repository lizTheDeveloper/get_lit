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
CRGB strip[NUM_LEDS][9];

//contains the rain fill level
static uint8_t countHolder = NUM_LEDS; 
static uint8_t hue = 0;
static uint8_t hueAlt = 20;


void setup() { 
  Serial.begin(57600);
  Serial.println("resetting");
  // LEDs are at addresses //36 - 52, step 2
  LEDS.addLeds<WS2812,36,RGB>(strip[0],NUM_LEDS);
  LEDS.addLeds<WS2812,38,RGB>(strip[1],NUM_LEDS);
  LEDS.addLeds<WS2812,40,RGB>(strip[2],NUM_LEDS);
  LEDS.addLeds<WS2812,42,RGB>(strip[3],NUM_LEDS);
  LEDS.addLeds<WS2812,44,RGB>(strip[4],NUM_LEDS);
  LEDS.addLeds<WS2812,46,RGB>(strip[5],NUM_LEDS);
  LEDS.addLeds<WS2812,48,RGB>(strip[6],NUM_LEDS);
  LEDS.addLeds<WS2812,50,RGB>(strip[7],NUM_LEDS);
  LEDS.addLeds<WS2812,52,RGB>(strip[8],NUM_LEDS);
  
  LEDS.setBrightness(84);
}

//void fadeall(CRGB strip) { 
//  for(int i = 0; i < NUM_LEDS; i++) {
//    strip[i].nscale8(250); 
//  } 
//}



void loop() { 
  //march across strips
  for (int march = 0; march < 9; march++) {
    for (int i=0; i < NUM_LEDS; i++) {
      strip[march][i] = CHSV(hue + (march * 5), 255, 255);
      delay(10);
    }
    FastLED.show();
    hue += 10;
  }
}
