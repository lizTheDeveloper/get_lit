
static const uint8_t BOOMS_PER_FIREWORK = 7;

typedef struct {
  float loc;
  uint8_t hue;
  float val;
  float velocity; // Negative is down, positive is up
} Particle;

typedef struct {
  // all associated logic will live inside receptacle_fireworks for now.
  uint8_t state; // 0 -> waiting, 1 -> ascending, 2 -> bursting. TODO: use a real enum lolz
  Particle rocket;
  Particle booms[BOOMS_PER_FIREWORK];
} Firework;

void receptacle_fireworks() {
  static const uint8_t FIREWORK_COUNT = 7;
  static const uint8_t FIREWORK_OUTER_COUNT = 4;
  static const float GRAVITY = -0.05;
  static Firework fireworks[FIREWORK_COUNT];
  static bool initialized = false;
  static const float SPLODE_VELOCITY = 0.3;

  // when bursting, 0..<SHIMMER_FACTOR is randomly added to all values
  static const uint8_t SHIMMER_FACTOR = 40;

  if (initialized == false) {
    initialized = true;

    for (int f = 0; f < FIREWORK_COUNT; f++) {
      fireworks[f].state = 0; // Waiting
    }
  }

  
  // Reset to black
  for (int i = 0; i < OUTER_RECEPTACLE_LED_COUNT; i++) {
    outer_receptacle_leds[i] = CHSV(0, 255, 0);
    
    if (i < INNER_RECEPTACLE_LED_COUNT) {
        inner_receptacle_leds[i] = CHSV(0, 255, 0);
     }
  }

  for (int f = 0; f < FIREWORK_COUNT; f++) {

    if (fireworks[f].state == 0) {
      // Waiting

      if (random8(255) == 0) {

        fireworks[f].state = 1;

        fireworks[f].rocket.hue = 0;
        fireworks[f].rocket.loc = 0;
        fireworks[f].rocket.velocity = 2.15 - random8(50) * 0.003;
        if (f >= FIREWORK_OUTER_COUNT) {
          // Bit softer on the inside one
          fireworks[f].rocket.velocity -= 0.25;
        }
        fireworks[f].rocket.val = 100;
      }
    } else if (fireworks[f].state == 1) {
      // Ascending

      if (fireworks[f].rocket.velocity > SPLODE_VELOCITY) {
        // keep zooming up

        if (f < FIREWORK_OUTER_COUNT) {
          // TODO: Abstract this obvsy
          outer_receptacle_leds[(int) fireworks[f].rocket.loc] = CHSV(
            fireworks[f].rocket.hue,
            100,
            (int) fireworks[f].rocket.val
          );
        } else {
          
          inner_receptacle_leds[(int) fireworks[f].rocket.loc] = CHSV(
            fireworks[f].rocket.hue,
            100,
            (int) fireworks[f].rocket.val
          );
        }

        fireworks[f].rocket.loc += fireworks[f].rocket.velocity;
        fireworks[f].rocket.velocity += GRAVITY;

        Serial.println(fireworks[f].rocket.loc);

      } else {
        // boom
        fireworks[f].state = 2;

        uint8_t hue = random8();

        // Now we have fireworks
        for (int b = 0; b < BOOMS_PER_FIREWORK; b++) {
          fireworks[f].booms[b].loc = fireworks[f].rocket.loc;
          fireworks[f].booms[b].hue = hue;
          fireworks[f].booms[b].val = 255 - SHIMMER_FACTOR;
          fireworks[f].booms[b].velocity = SPLODE_VELOCITY + (-0.2 * (BOOMS_PER_FIREWORK - 1) / 2) + (0.2 * b);
        }        
        
        // Bye rocket
      }
    } else {
      // Bursting

      for (int b = 0; b < BOOMS_PER_FIREWORK; b++) {
        if (fireworks[f].booms[b].val < 0) {
          fireworks[f].state = 0;
          break;
        }
  
        if (fireworks[f].booms[b].loc < 0) {
          if (b == BOOMS_PER_FIREWORK - 1) {
            fireworks[f].state = 0;
          }
          continue;
        }
    
        if (f < FIREWORK_OUTER_COUNT) {
          // TODO: Abstract this
          outer_receptacle_leds[(int) fireworks[f].booms[b].loc] = CHSV(
            fireworks[f].booms[b].hue,
            255,
            random8(SHIMMER_FACTOR) + (int) fireworks[f].booms[b].val
          );
        } else {
          inner_receptacle_leds[(int) fireworks[f].booms[b].loc] = CHSV(
            fireworks[f].booms[b].hue,
            255,
            random8(SHIMMER_FACTOR) + (int) fireworks[f].booms[b].val
          );
        }
  
        fireworks[f].booms[b].loc += fireworks[f].booms[b].velocity;
        fireworks[f].booms[b].velocity += GRAVITY;
        fireworks[f].booms[b].val -= 5;
      }
    }
  }

}

