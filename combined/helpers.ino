#include "FastLED.h"

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
