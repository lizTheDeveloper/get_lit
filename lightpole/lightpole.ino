#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 28

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 8
#define CLOCK_PIN 13


// Define the array of leds
CRGB strip[NUM_LEDS][9];

void setup() { 
  Serial.begin(57600);
  Serial.println("resetting");
  // LEDs are at addresses //36 - 52, step 2
  LEDS.addLeds<WS2812,36,RGB>(strip[0],NUM_LEDS);
  LEDS.addLeds<WS2812,38,RGB>(strip[1],NUM_LEDS);
  LEDS.addLeds<WS2812,40,RGB>(strip[2],181);// light pole 
  LEDS.addLeds<WS2812,42,RGB>(strip[3],NUM_LEDS);
  LEDS.addLeds<WS2812,44,RGB>(strip[4],NUM_LEDS);
  LEDS.addLeds<WS2812,46,RGB>(strip[5],NUM_LEDS);
  LEDS.addLeds<WS2812,48,RGB>(strip[6],NUM_LEDS);
  LEDS.addLeds<WS2812,50,RGB>(strip[7],NUM_LEDS);
  LEDS.addLeds<WS2812,52,RGB>(strip[8],NUM_LEDS);
  
  LEDS.setBrightness(84);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i < 181; i++) {
    strip[0][i] = CHSV(i * 20, 255, 255);
    FastLED.show();
    delay(10);
  }
}
