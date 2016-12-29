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

const int NUM_PINS = 2;
const long FADE_DELAY = 8; // ms; controls fade speed

// offset bounds for random offset
const int MIN_OFFSET = 0;
const int MAX_OFFSET = 200;

// random offsets for each iteration
int randOffsets[NUM_PINS];

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }

  // generate random offsets
  for (int pin = 0; pin < NUM_PINS; pin++) {
    randOffsets[pin] = random(MIN_OFFSET, MAX_OFFSET);
  }
}

void loop() {
  // increase output
  for (int i = 0; i < 255; i++) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, (i + randOffsets[pin]) % 256);
    }
    delay(FADE_DELAY);
  } 
  
  // decrease output
  for (int i = 255; i > 0; i--) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, (i + randOffsets[pin]) % 256);
    }
    delay(FADE_DELAY);
  }
}
