
typedef struct {
  uint16_t loc;
  uint8_t age;
} Sparkle;

void spiral_sparkles() {
  static const uint8_t SPARKLE_MAX_AGE = 254;
  static const uint8_t SPARKLE_COUNT = 50;

  static Sparkle sparkles[SPARKLE_COUNT];
  static bool initialized = false;

  if (initialized == false) {
    initialized = true;

    for (int s = 0; s < SPARKLE_COUNT; s++) {
      sparkles[s].loc = random8(SPIRAL_LED_COUNT);
      sparkles[s].age = random8(SPARKLE_MAX_AGE);
    }
  }

  for (int s = 0; s < SPARKLE_COUNT; s++) {
    if (sparkles[s].age < SPARKLE_MAX_AGE) {
      sparkles[s].age += 1;

      uint8_t value = sin8((sparkles[s].age + 192) % 256);
      
      spiral_leds[sparkles[s].loc] = CHSV(0, 0, value);
    } else {
      spiral_leds[sparkles[s].loc] = CHSV(0, 0, 0);
      if (random8(100) < 3) {
        Serial.print("Resetting slot ");
        Serial.println(s);
        sparkles[s].age = 0;
        sparkles[s].loc = random(SPIRAL_LED_COUNT);
      }
    }
  }
    
}


// TODO: Merge this with the spiral_sparkles code.
// It only differs in SPARKLE_COUNT, the `.loc =` lines, and `set_led(` lines.

void all_sparkles() {
  static const uint8_t SPARKLE_MAX_AGE = 254;
  static const uint8_t SPARKLE_COUNT = 100;

  static Sparkle sparkles[SPARKLE_COUNT];
  static bool initialized = false;

  if (initialized == false) {
    initialized = true;

    for (int s = 0; s < SPARKLE_COUNT; s++) {
      sparkles[s].loc = random16(TOTAL_LED_COUNT);
      sparkles[s].age = random8(SPARKLE_MAX_AGE);
    }
  }

  for (int s = 0; s < SPARKLE_COUNT; s++) {
    if (sparkles[s].age < SPARKLE_MAX_AGE) {
      sparkles[s].age += 1;

      uint8_t value = sin8((sparkles[s].age + 192) % 256);
      
      set_led(sparkles[s].loc, CHSV(0, 0, value));
    } else {
      set_led(sparkles[s].loc, CHSV(0, 0, 0));
      if (random8(100) < 3) {
        Serial.print("Resetting slot ");
        Serial.println(s);
        sparkles[s].age = 0;
        sparkles[s].loc = random16(TOTAL_LED_COUNT);
      }
    }
  }
    
}

