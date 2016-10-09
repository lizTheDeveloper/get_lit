#include "FastLED.h"

///// Unused Thoughts

//typedef uint16_t LEDUniversalIndex;
//
//enum LEDSection {
//  SPHERE_SECTION,
//  SPIRAL_SECTION,
//  RECEPTACLE_SECTION,
//  ALL_SECTIONS,
//};
//
//LEDUniversalIndex random_led_index_from_section(LEDSection section) {
//  // TODO: Flesh this out, start using it.
//}

/////


// "i" indexes into all LEDs in one group from 0..<TOTAL_LED_COUNT
// Mostly useful for completely position-agnostic (random?) patterns.
void set_led(uint16_t i, CRGB color) {
  if (i < TOTAL_SPHERE_LED_COUNT) {
    sphere_leds[i % SPHERE_STRIP_COUNT][i / SPHERE_STRIP_COUNT] = color;
    return;
  } 

  i -= TOTAL_SPHERE_LED_COUNT;
  
  if (i < SPIRAL_LED_COUNT) {
    spiral_leds[i] = color;
    return;
  }

  i -= SPIRAL_LED_COUNT;

  if (i < INNER_RECEPTACLE_LED_COUNT) {
    inner_receptacle_leds[i] = color;
    return;
  }

  i -= INNER_RECEPTACLE_LED_COUNT;

  if (i < OUTER_RECEPTACLE_LED_COUNT) {
    outer_receptacle_leds[i] = color;
    return;
  }

  // shouldn't get here.
}

void set_extended_strip_led(uint8_t strip, uint8_t i, CRGB color) {
  if (i < SPHERE_LED_COUNT) {
    sphere_leds[strip][i] = color;
  } else {
    
    const uint8_t spiral_index = 
      (i - SPHERE_LED_COUNT + 1) * SPIRAL_CIRCUMFERENCE_APPROX // space it out vertically
      + strip * 3 // space it out around the barrel
      + 3 // eyeballed alignment calibration
    ;

    if (spiral_index < SPIRAL_LED_COUNT) {
      spiral_leds[spiral_index] = color;
    }
  }
}



void fade_all_spiral_leds_by(uint8_t fade) { 
  for(int i = 0; i < SPIRAL_LED_COUNT; i++) {
    spiral_leds[i].nscale8(254);
  }
}

void fade_all_sphere_leds_by(uint8_t fade) { 
  for(int strip = 0; strip < 8; strip++) { 
    for(int i = 0; i < SPHERE_LED_COUNT; i++) {
      sphere_leds[strip][i].nscale8(254); 
    }
  }
}
