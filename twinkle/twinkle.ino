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

#define NUM_PINS 5
#define FADE_DELAY 10 // ms; controls fade speed
#define UPPER_BRIGHTNESS 255 // the brightness range to use
#define LOWER_BRIGHTNESS 100 // (only the upper end to make a subtle effect)

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() { 
  // Note: becasue only 3 out of 5 pins support analog output (PWM), 
  // the digital pins will just be either on or off based on this value
  
  // gradually increase brightness in the range for all pins
  for (int i = LOWER_BRIGHTNESS; i < UPPER_BRIGHTNESS; i++) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, i);
    }
    delay(FADE_DELAY);
  } 
  
  // gradually decrease brightness in the range for all pins
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
