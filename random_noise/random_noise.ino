/*
 * random_noise.ino
 * 
 * ATtiny85 Project
 * Randomly varies output on all pins
 * 
 * 12.28.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

const int NUM_PINS = 5;
const long RESET_TIME = 200; // ms; duration to wait before getting new random values

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < NUM_PINS; i++) {
    // write a random voltage
    analogWrite(i, random(0, 255));
  }  
  delay(RESET_TIME);
}
