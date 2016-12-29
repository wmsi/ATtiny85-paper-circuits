/*
 * fade_with_input.ino
 * 
 * ATtiny85 Project
 * Fades output based on the value of an analog input
 * 
 * 12.28.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

const int INPUT_PIN = A2;
const int NUM_PINS = 2;
const int LOWEST_INPUT = 0; // input that should be min output
const int HIGHEST_INPUT = 1023; // input that should be max output 
int input = 0, output = 0;

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(INPUT_PIN, INPUT);
}

void loop() {
  input = analogRead(INPUT_PIN);

  output = map(input, LOWEST_INPUT, HIGHEST_INPUT, 0, 255); 
  for (int pin = 0; pin < NUM_PINS; pin++) {
    analogWrite(pin, output);
  }

  // slow it down a bit
  delay(2);
}
