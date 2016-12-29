/*
 * twinkle.ino
 * 
 * ATtiny85 Project
 * Produces a star-like "twinkle" effect
 * 
 * 12.28.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

const int NUM_PINS = 5;
const long FADE_DELAY = 10; // ms; controls fade speed
const long UPPER_BRIGHTNESS = 255;
const long LOWER_BRIGHTNESS = 100;

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {  
    // increase output
  for (int i = LOWER_BRIGHTNESS; i < UPPER_BRIGHTNESS; i++) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, i);
    }
    delay(FADE_DELAY);
  } 
  
  // decrease output
  for (int i = UPPER_BRIGHTNESS; i > LOWER_BRIGHTNESS; i--) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, i);
    }
    delay(FADE_DELAY);
  } 

      // alternate method
//    for (int pin = 0; pin < NUM_PINS; pin++) {
//      analogWrite(pin, random(LOWER_BRIGHTNESS, UPPER_BRIGHTNESS));
//    }
//    delay(FADE_DELAY);
}
