/*
 * sounds.ino
 * 
 * ATtiny85 Project
 * Plays various tones (when hooked to a speaker) using PWM
 * 
 * 12.28.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

const int NUM_PINS = 1;
const long FADE_DELAY = 60; // ms; controls fade speed

void setup() {
    pinMode(0, OUTPUT);
}

void loop() {
  // increase output
  for (int i = 0; i < 255; i++) {
    analogWrite(0, i);
    delay(FADE_DELAY);
  } 
  
  // decrease output
  for (int i = 255; i > 0; i--) {
    analogWrite(0, i);
    delay(FADE_DELAY);
  }
}
