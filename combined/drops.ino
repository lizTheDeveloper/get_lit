
typedef struct {
  uint8_t loc;
  uint8_t strip;
} Drop;

// This sends drops down the sphere and then spiral, at random intervals :]
// I'm pretty happy with this one :] -J
void gumball_spiraling_randoms() {
  static bool initialized = false;
  static const uint8_t DROP_COUNT = 12;
  static const uint8_t DROP_PERCENT_CHANCE = 3; //originally 2
  static const uint8_t SPHERE_FADE = 220; //lower means shorter drops 230 is original for both
  static const uint8_t SPIRAL_FADE = 180;
  static const uint8_t CYCLES_BETWEEN_DROPS = 10; //originally 10

  static Drop drops[DROP_COUNT];
  static uint8_t last_three_strips[3];
  static uint8_t cycles_since_last_drop = 0;

  if (initialized == false) {
    initialized = true;
    for (int i = 0; i < DROP_COUNT; i++) {
      drops[i].loc = random(SPIRAL_LED_COUNT);
      drops[i].strip = random8(SPHERE_STRIP_COUNT);
    }
  }

  // Fade all
  for (int i = 0; i < SPIRAL_LED_COUNT; i++) {
    spiral_leds[i].nscale8(SPIRAL_FADE);
  }

  for (int i = 0; i < SPHERE_LED_COUNT; i++) {
    for (int strip = 0; strip < 8; strip++) {
      sphere_leds[strip][i].nscale8(SPHERE_FADE);
    }
  }

  cycles_since_last_drop += 1;

  // Refresh the drops
  for (int d = 0; d < DROP_COUNT; d++) {
    uint8_t hue = d * (255 / DROP_COUNT);

    if (drops[d].loc < SPHERE_LED_COUNT) {
      // Dropping down the sphere
      sphere_leds[drops[d].strip][SPHERE_LED_COUNT - drops[d].loc - 1] = CHSV(hue, 255, 255);
      drops[d].loc += 1;
    } else if (drops[d].loc < SPHERE_LED_COUNT + SPIRAL_LED_COUNT) {
      // Dropping down the strip
      spiral_leds[SPIRAL_LED_COUNT - drops[d].loc + SPHERE_LED_COUNT - 1] = CHSV(hue, 255, 255);
      drops[d].loc += 1;
    } else {
      // This drop is done. Random chance of restarting.
      if (cycles_since_last_drop > CYCLES_BETWEEN_DROPS && random(100) < DROP_PERCENT_CHANCE) {
        cycles_since_last_drop = 0;

        if (false) {
          // Debug printing
          Serial.print("restarting");
          Serial.print(d);
          Serial.print(" - ");
          for (int dd = 0; dd < DROP_COUNT; dd++) {
            Serial.print(drops[dd].loc);
            Serial.print(",");
          }
          Serial.println("");
        }
        
        drops[d].loc = 0;

        uint8_t random_strip = random8(SPHERE_STRIP_COUNT);

        while (random_strip == last_three_strips[0]
            || random_strip == last_three_strips[1]
            || random_strip == last_three_strips[2]) {
          random_strip = random8(SPHERE_STRIP_COUNT);
        }

        last_three_strips[2] = last_three_strips[1];
        last_three_strips[1] = last_three_strips[0];
        last_three_strips[0] = random_strip;
        
        drops[d].strip = random_strip;
        spiral_leds[SPIRAL_LED_COUNT - drops[d].loc - 1] = CHSV(hue, 255, 255);
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
