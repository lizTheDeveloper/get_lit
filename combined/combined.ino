#include "FastLED.h"

#define DATA_PIN 8
#define CLOCK_PIN 13

#define SPHERE_LED_COUNT 28 // Final count
#define SPIRAL_LED_COUNT 163 // Final count
#define RECEPTACLE_LED_COUNT 20

// LED Arrays
CRGB sphere_leds[8][SPHERE_LED_COUNT];
CRGB spiral_leds[SPIRAL_LED_COUNT];
CRGB receptacle_leds[2][RECEPTACLE_LED_COUNT];


void setup() {

  Serial.begin(57600);
  Serial.println("resetting");

  // Don't use pin 20!!

  // Sphere
  // Blue green yellow orange purple gray white black
  // 22 -> 36
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

  // Receptacle (not working)
//  LEDS.addLeds<WS2812,46,RGB>(receptacle_leds[0],RECEPTACLE_LED_COUNT);
//  LEDS.addLeds<WS2812,48,RGB>(receptacle_leds[1],RECEPTACLE_LED_COUNT);

  FastLED.setBrightness(30);
}

void loop() {

  sphere_drops();
//  failing_receptacle_check();
}

void failing_receptacle_check() {
  static uint8_t hue = 0;

  for (int i = 0; i < RECEPTACLE_LED_COUNT; i++) {
    receptacle_leds[i] = CHSV(hue++, 255, 255);
  }

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

