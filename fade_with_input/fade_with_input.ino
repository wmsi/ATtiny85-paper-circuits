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

#define INPUT_PIN A2
#define NUM_PINS 2
#define LOWEST_INPUT 0 // input that should be min output
#define HIGHEST_INPUT 1023 // input that should be max output 
int input = 0, output = 0;

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(INPUT_PIN, INPUT);
}

void loop() {
  input = analogRead(INPUT_PIN);

  // convert the analog input to a normal analog output value (0 - 255)
  output = map(input, LOWEST_INPUT, HIGHEST_INPUT, 0, 255); 

  // write that adjusted value to all pins
  for (int pin = 0; pin < NUM_PINS; pin++) {
    analogWrite(pin, output);
  }

  // slow it down a bit for stability
  delay(2);
}
