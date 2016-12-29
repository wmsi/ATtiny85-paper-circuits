/*
 * fade.ino
 * 
 * ATtiny85 Project
 * Fades output on all pins using PWM
 * 
 * 12.28.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

const int NUM_PINS = 2;
const long FADE_DELAY = 8; // ms; controls fade speed

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // increase output
  for (int i = 0; i < 255; i++) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, i);
    }
    delay(FADE_DELAY);
  } 
  
  // decrease output
  for (int i = 255; i > 0; i--) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, i);
    }
    delay(FADE_DELAY);
  }
}
