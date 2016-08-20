#include "FastLED.h"

#define DATA_PIN 8
#define CLOCK_PIN 13

#define SPHERE_STRIP_COUNT 8

#define EXTENDED_STRIP_LED_COUNT 34

#define SPHERE_LED_COUNT 28
#define SPIRAL_LED_COUNT 163
#define INNER_RECEPTACLE_LED_COUNT 47
#define OUTER_RECEPTACLE_LED_COUNT 56

#define SPIRAL_CIRCUMFERENCE_APPROX 25

// LED Arrays
CRGB sphere_leds[SPHERE_STRIP_COUNT][SPHERE_LED_COUNT];
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
  LEDS.addLeds<WS2812,22,RGB>(sphere_leds[2],SPHERE_LED_COUNT);
  LEDS.addLeds<WS2812,28,RGB>(sphere_leds[3],SPHERE_LED_COUNT);
  LEDS.addLeds<WS2812,32,RGB>(sphere_leds[4],SPHERE_LED_COUNT);
  LEDS.addLeds<WS2812,36,RGB>(sphere_leds[5],SPHERE_LED_COUNT);
  LEDS.addLeds<WS2812,30,RGB>(sphere_leds[6],SPHERE_LED_COUNT);
  LEDS.addLeds<WS2812,34,RGB>(sphere_leds[7],SPHERE_LED_COUNT);

  // Spiral
  LEDS.addLeds<WS2812,40,RGB>(spiral_leds,SPIRAL_LED_COUNT);

  // Receptacle
  LEDS.addLeds<WS2812,46,RGB>(inner_receptacle_leds,INNER_RECEPTACLE_LED_COUNT);
  LEDS.addLeds<WS2812,48,RGB>(outer_receptacle_leds,OUTER_RECEPTACLE_LED_COUNT);

  FastLED.setBrightness(10);

//  for (int i = 0; i < 255; i++) {
//    Serial.print(i);
//    Serial.print(" ");
//    Serial.println(cos8(i));
//  }
}

void loop() {

  gumball_spiraling_randoms();
//  spiral_sparkles();
  receptacle_drops();


  FastLED.show();
  delay(10);
}

/////////////// Unhomed Patterns

void test_vertical_alignment() {
  for (int strip = 0; strip < SPHERE_STRIP_COUNT; strip++) {
    for (int i = 0; i < EXTENDED_STRIP_LED_COUNT; i++) {
      set_extended_strip_led(strip, i, CHSV(strip * 32, 255, 255));
    }

    FastLED.show();
    delay(250);

//    for (int i = 0; i < EXTENDED_STRIP_LED_COUNT; i++) {
//      set_extended_strip_led(strip, i, CHSV(0, 100, 0));
//    }
  }
}



void receptacle_sizzle() {
  static uint8_t spin = 0;

  for (int i = 0; i < OUTER_RECEPTACLE_LED_COUNT; i++) {

    bool should_light_outer = (spin + i) % 12 == 0;
    bool should_light_inner = (spin + i) % 12 == 6;

    if (should_light_outer) {
      outer_receptacle_leds[i] = CHSV(spin + i, 255, (should_light_outer) ? 100 : 0);
    } else {
      outer_receptacle_leds[i].fadeToBlackBy(64);
    }
    
    if (i < INNER_RECEPTACLE_LED_COUNT) {
      if (should_light_inner) {
        inner_receptacle_leds[i] = CHSV(spin + i, 255, (should_light_inner) ? 100 : 0);
      } else {
        inner_receptacle_leds[i].fadeToBlackBy(64);
      }
    }
  }

  spin += 1;
}


void gumball_fill_up() {

  // WIP; the fading isn't working for some reason
  
  static uint8_t spin = 0;

  if (spin < SPIRAL_LED_COUNT) {
    uint8_t i = spin;
    spiral_leds[i] = CHSV(0, 100, 50);
  } else if (spin < SPIRAL_LED_COUNT + SPHERE_LED_COUNT) {
    uint8_t i = spin - SPIRAL_LED_COUNT;
    for (int strip = 0; strip < 8; strip++) {
      sphere_leds[strip][i] = CHSV(0, 10, 50);
    }
  } else {
    delay(100);
    fade_all_spiral_leds_by(252);
    fade_all_sphere_leds_by(252);
  }

  delay(10);
  spin += 1;
  
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
}


// This sends drops down the spiral at predictable intervals :0
void spiral_spiraling_singles() {
  static const uint8_t frequency = 10;
  static const uint8_t cycle_length = 255 - (255 % frequency);
  static const uint8_t color_multiple = 7; // Try to get this relatively prime vs frequency

  static uint8_t spin = 0;
  spin = (spin + 1) % cycle_length;

  for (int i = 0; i < SPIRAL_LED_COUNT; i++) {
    bool should_light = ((spin + i) % frequency) == 0;

    if (should_light) {
      spiral_leds[i] = CHSV(
//        i * 1.5,
        (color_multiple * (spin + i)) % cycle_length,
        255,
        (should_light) ? 100 : 0
      );
    } else {
      spiral_leds[i].fadeToBlackBy(50);  
    }
  }
}

// This 
void spiral_slowly_throbbing() {
  static uint8_t hue = 0;
  hue += 1; // Naturally cycles around 255

  for (int i = 0; i < SPIRAL_LED_COUNT; i++) {
    spiral_leds[i] = CHSV(hue + i, 255, 100);
  }
}


