

// This sends drops down the sphere and then spiral, at random intervals :]
// I'm pretty happy with this one :] -J
void gumball_spiraling_randoms() {
  static bool initialized = false;
  static const uint8_t DROP_COUNT = 8;
  static const uint8_t DROP_PERCENT_CHANCE = 2;

  static uint8_t drops[DROP_COUNT];
  static uint8_t cycles_since_last_drop = 0;

  if (initialized == false) {
    initialized = true;
    for (int i = 0; i < DROP_COUNT; i++) {
      drops[i] = random(SPIRAL_LED_COUNT);
    }
  }

  // Fade all
  for (int i = 0; i < SPIRAL_LED_COUNT; i++) {
    spiral_leds[i].nscale8(230);
  }

  for (int i = 0; i < SPHERE_LED_COUNT; i++) {
    for (int strip = 0; strip < 8; strip++) {
      sphere_leds[strip][i].nscale8(230);
    }
  }

  cycles_since_last_drop += 1;

  // Refresh the drops
  for (int d = 0; d < DROP_COUNT; d++) {
    uint8_t hue = d * (255 / DROP_COUNT);

    if (drops[d] < SPHERE_LED_COUNT) {
      // Dropping down the sphere
      sphere_leds[d][SPHERE_LED_COUNT - drops[d] - 1] = CHSV(hue, 255, 255);
      drops[d] += 1;
    } else if (drops[d] < SPHERE_LED_COUNT + SPIRAL_LED_COUNT) {
      // Dropping down the strip
      spiral_leds[SPIRAL_LED_COUNT - drops[d] + SPHERE_LED_COUNT - 1] = CHSV(hue, 255, 255);
      drops[d] += 1;
    } else {
      // This drop is done. Random chance of restarting.
      if (cycles_since_last_drop > 10 && random(100) < DROP_PERCENT_CHANCE) {
        cycles_since_last_drop = 0;

        if (false) {
          // Debug printing
          Serial.print("restarting");
          Serial.print(d);
          Serial.print(" - ");
          for (int dd = 0; dd < DROP_COUNT; dd++) {
            Serial.print(drops[dd]);
            Serial.print(",");
          }
          Serial.println("");
        }
        
        drops[d] = 0;
        spiral_leds[SPIRAL_LED_COUNT - drops[d] - 1] = CHSV(hue, 255, 255);
      }
    }
  }
}


void spiral_drops() {
  static uint8_t hue = 0;

  for (int i = 0; i < SPIRAL_LED_COUNT; i++) {
    bool should_light = (i % 10) == 0;
    spiral_leds[i] = CHSV(hue + i, 255, (should_light) ? 100 : 0);
  }

  hue += 1;
}

void sphere_drops() {
  static uint8_t hue = 0;

  static uint8_t val = 0;

  static uint8_t MAX_VAL = 15;

  for(int strip = 0; strip < 8; strip++) { 
    for(int i = 0; i < SPHERE_LED_COUNT; i++) {
 
      bool should_light = ((MAX_VAL-1) - (3 * strip + i) % MAX_VAL == val);

      if (should_light) {
        sphere_leds[strip][i] = CHSV(
          /* Hue */ hue++,
          /* Sat */ 255,
          /* Val */ (should_light) ? 100 : 0
        );
      } else {
        sphere_leds[strip][i].fadeToBlackBy(64);
      }
            
    }
  }

  val = (val + 1) % MAX_VAL;
}

