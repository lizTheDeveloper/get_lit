//
//void fadeall() { 
//  for(int i = 0; i < NUM_LEDS; i++) {
//    leds[i].nscale8(250); 
//  } 
//}
//
//void gumball() { 
//  static uint8_t hue = 0;
//  static uint8_t flashHolder = 0;
//  static uint8_t hueRange = 10;
//  Serial.println("x");
//  // First slide the led in one direction
//  for(int i = 0; i < NUM_LEDS; i++) {
//    // Set the i'th led to red 
//    leds[i] = CHSV(hue++, 255, 255);
//    // Show the leds
//    FastLED.show(); 
//    // now that we've shown the leds, reset the i'th led to black
//    // leds[i] = CRGB::Black;
//    fadeall();
//    // Wait a little bit before we loop around and do it again
//    delay(10);
//  }
//  Serial.print("x");
//
//  //crazy flash
//  // log g and b to the r gives you fire 
//  
//  for(int i = 0; i < NUM_LEDS; i++) {
//    // Set the i'th led to red 
//    leds[i] = CHSV(flashHolder+=10, 255, 255);
//    // Show the leds
//    FastLED.show(); 
//    // now that we've shown the leds, reset the i'th led to black
//    // leds[i] = CRGB::Black;
//    fadeall();
//    // Wait a little bit before we loop around and do it again
//    delay(10);
//  }
//
//  // Now go in the other direction.  
//  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
//    // Set the i'th led to red 
//    leds[i] = CHSV(hue++, 255, 255);
//    // Show the leds
//    FastLED.show();
//    // now that we've shown the leds, reset the i'th led to black
//    // leds[i] = CRGB::Black;
//    fadeall();
//    // Wait a little bit before we loop around and do it again
//    delay(10);
//  }
//  
////  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
////    leds[i] = CHSV(hue, 255, 255);
////    FastLED.show();
////    delay(10);
////  }
////  hue = hue + 10 % 256;
//}
