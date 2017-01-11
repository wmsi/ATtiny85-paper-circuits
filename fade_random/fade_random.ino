/*
 * fade_random.ino
 * 
 * ATtiny85 Project
 * Fades output on all pins using PWM, but with random offsets
 * 
 * 12.28.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

// TODO: Not continious!!

#define NUM_PINS 2
#define FADE_DELAY 8 // ms; controls fade speed

// offset bounds for random brightness offset
// (max would be from 0 to 255
#define MIN_OFFSET 0
#define MAX_OFFSET 200

// random brightness offsets to apply
int randOffsets[NUM_PINS];

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }

  // generate random brightness offsets for each pin
  for (int pin = 0; pin < NUM_PINS; pin++) {
    randOffsets[pin] = random(MIN_OFFSET, MAX_OFFSET);
  }
}

void loop() {
  // gradually increase output for each pin
  for (int i = 0; i < 255; i++) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      // add a the random offset for each pin to try to make them fade slightly differently
      // (use modulus to wrap the output around if it's over 255)
      analogWrite(pin, (i + randOffsets[pin]) % 256);
    }
    delay(FADE_DELAY);
  }
  
  // decrease output, applying random offsets again
  for (int i = 255; i > 0; i--) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, (i + randOffsets[pin]) % 256);
    }
    delay(FADE_DELAY);
  }

  // the theory is that the brightness will be continious (i.e. won't jump) 
  // when this loops around because we're using the same random offset, 
  // but it doesn't seem to work...
}
