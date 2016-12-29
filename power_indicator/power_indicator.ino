/*
 * power_indicator.ino
 * 
 * ATtiny85 Project
 * Uses a series of pins (with LEDs for example) to indicate the power level 
 * being applied to a certain input pin.
 * 
 * 12.28.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

const int FIRST_PIN = 0; // first pin in series of NUM_PINS
const int NUM_PINS = 4;
const int INPUT_PIN = A2; // pin to read from
const int LOWEST_INPUT = 0; // input that should bottom out the power indicator
const int HIGHEST_INPUT = 1023; // input that should max out the power indicator

int reading = 0;
int powerLevel = 0; // last pin in power indicator "bar"

void setup() {  
  for (int i = FIRST_PIN; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(INPUT_PIN, INPUT);
}

void loop() {
  reading = analogRead(INPUT_PIN);

  // convert the analog reading to a pin index
  powerLevel = map(reading, LOWEST_INPUT, HIGHEST_INPUT, FIRST_PIN, NUM_PINS);
  
  for (int i = FIRST_PIN; i < powerLevel; i++) {
    if (i == powerLevel - 1) {
      digitalWrite(i, HIGH);
    }
    else {
      digitalWrite(i, LOW);
    }
  }

  // make sure the rest of the pins are shut off
  for (int i = powerLevel; i < NUM_PINS; i++) {    
    if (i != powerLevel - 1) {
      digitalWrite(i, LOW);
    }
  }

  // slow it down a bit
  delay(2);
}
