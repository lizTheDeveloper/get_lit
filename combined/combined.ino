#include "FastLED.h"

#define DATA_PIN 8
#define CLOCK_PIN 13

#define SPHERE_LED_COUNT 28 // Final count
#define SPIRAL_LED_COUNT 163 // Final count
#define INNER_RECEPTACLE_LED_COUNT 47 // Final count
#define OUTER_RECEPTACLE_LED_COUNT 56 // Final count

// LED Arrays
CRGB sphere_leds[8][SPHERE_LED_COUNT];
CRGB spiral_leds[SPIRAL_LED_COUNT];
CRGB inner_receptacle_leds[INNER_RECEPTACLE_LED_COUNT];
CRGB outer_receptacle_leds[OUTER_RECEPTACLE_LED_COUNT];


void setup() {

  // The serial monitor's speed setting must match this number or you'll see garbage.
  Serial.begin(57600 /* baud */);
  Serial.println("resetting");

  // Don't use pin 20!!

  // Sphere
  // Pin order: blue green yellow orange purple gray white black
  // 22 -> 36 (non-consecutive in the settings below)
  LEDS.addLeds<WS2812,24,RGB>(sphere_leds[0],SPHERE_LED_COUNT);
  LEDS.addLeds<WS2812,26,RGB>(sphere_leds[1],SPHERE_LED_COUNT);
  LEDS.addLeds<WS2812,28,RGB>(sphere_leds[2],SPHERE_LED_COUNT);
  LEDS.addLeds<WS2812,22,RGB>(sphere_leds[3],SPHERE_LED_COUNT);
  LEDS.addLeds<WS2812,36,RGB>(sphere_leds[4],SPHERE_LED_COUNT);
  LEDS.addLeds<WS2812,32,RGB>(sphere_leds[5],SPHERE_LED_COUNT);
  LEDS.addLeds<WS2812,30,RGB>(sphere_leds[6],SPHERE_LED_COUNT);
  LEDS.addLeds<WS2812,34,RGB>(sphere_leds[7],SPHERE_LED_COUNT);

  // Spiral
  LEDS.addLeds<WS2812,40,RGB>(spiral_leds,SPIRAL_LED_COUNT);

  // Receptacle
  LEDS.addLeds<WS2812,46,RGB>(inner_receptacle_leds,INNER_RECEPTACLE_LED_COUNT);
  LEDS.addLeds<WS2812,48,RGB>(outer_receptacle_leds,OUTER_RECEPTACLE_LED_COUNT);

  FastLED.setBrightness(255);
}

void loop() {

  sphere_drops();
  spiral_slowly_throbbing();
  receptacle_slowly_throbbing();
}

void receptacle_slowly_throbbing() {
  static uint8_t hue = 0;

  for (int i = 0; i < OUTER_RECEPTACLE_LED_COUNT; i++) {
    outer_receptacle_leds[i] = CHSV(hue + i, 255, 255);
    if (i < INNER_RECEPTACLE_LED_COUNT) {
      inner_receptacle_leds[i] = CHSV(hue + i, 255, 255);
    }
  }

  hue += 1;

  FastLED.show();
}

void spiral_slowly_throbbing() {
  static uint8_t hue = 0;

  for (int i = 0; i < SPIRAL_LED_COUNT; i++) {
    spiral_leds[i] = CHSV(hue + i, 255, 255);
  }

  hue += 1;

  FastLED.show();
}

void spiral_drops() {
  static uint8_t hue = 0;

  for (int i = 0; i < SPIRAL_LED_COUNT; i++) {
    spiral_leds[i] = CHSV(hue + i, 255, 255);
  }

  hue += 1;

  FastLED.show();
}


void sphere_drops() {
  static uint8_t hue = 0;

  static uint8_t val = 0;

  static uint8_t MAX_VAL = 15;

  for(int strip = 0; strip < 8; strip++) { 
    for(int i = 0; i < SPHERE_LED_COUNT; i++) {
 
      bool should_light = ((MAX_VAL-1) - (3 * strip + i) % MAX_VAL == val);

      sphere_leds[strip][i] = CHSV(
        /* Hue */ hue++,
        /* Sat */ 127,
        /* Val */ (should_light) ? 100 : 0);
            
    }
  }

  FastLED.show(); 

  val = (val + 1) % MAX_VAL;

}


void fade_all_sphere_leds_slightly() { 
  for(int strip = 0; strip < 8; strip++) { 
    for(int i = 0; i < SPHERE_LED_COUNT; i++) {
      sphere_leds[strip][i].nscale8(250); 
    }
  }
}

