/*
 * blink_series.ino
 * 
 * ATtiny85 Project
 * Cycles through all output pins from 0 to 4 in a series, 
 * creating a blinking series effect on LEDs, etc. arranged in a line.
 * 
 * 12.28.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

#define NUM_PINS 5
#define BLINK_TIME 400 // ms; duration light is on for
#define RESET_TIME 0 // ms; duration to wait before looping again

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // go through all pins, blinking each on and off briefly
  for (int i = 0; i < NUM_PINS; i++) {    
    digitalWrite(i, HIGH);
    delay(BLINK_TIME);
    digitalWrite(i, LOW);
  }   
  
  delay(RESET_TIME);
}
