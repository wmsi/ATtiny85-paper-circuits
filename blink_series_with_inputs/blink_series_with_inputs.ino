/*
 * blink_series_with_inputs.ino
 * 
 * ATtiny85 Project
 * Cycles through all output pins from 0 to 2 in a series, 
 * creating a blinking series effect on LEDs, etc. arranged in a line.
 * Also controls the speed of the blinking effect using an analog input, 
 * and the direction is toggled using a button on a digital input.
 * 
 * 12.28.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

const int DIGITAL_IN_PIN = 3;
const int ANALOG_IN_PIN = A2;
const int NUM_PINS = 3;
const int MIN_BLINK_TIME = 10; // ms; min duration light is on for
const int MAX_BLINK_TIME = 500; // ms; max duration light is on for
const int LOWEST_INPUT = 0; // input that should be min blink speed
const int HIGHEST_INPUT = 1023; // input that should be max blink speed 
const long RESET_TIME = 2; // ms; duration to wait before looping again
const long DEBOUNCE_DELAY = 20;

// variables
int input = 0; 
long blinkTime = 0; // ms; variable duration light is on for

int buttonState = HIGH;
int buttonReading = HIGH;
int lastChangeTime = 0;

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(ANALOG_IN_PIN, INPUT);
  pinMode(DIGITAL_IN_PIN, INPUT);
}

void loop() {
  // get blink time from analog input
  input = analogRead(ANALOG_IN_PIN);
  blinkTime = map(input, LOWEST_INPUT, HIGHEST_INPUT, MIN_BLINK_TIME, MAX_BLINK_TIME);

  // execute blink series (we may be going either direction)
  for (int i = 0; i < NUM_PINS; i++) {
    // determine direction based on digital input
    int blinkPin = i;
    if (buttonState == HIGH)
      blinkPin = NUM_PINS - 1 - i;
    
    digitalWrite(blinkPin, HIGH);
    delay(blinkTime);
    digitalWrite(blinkPin, LOW);
  }

  // determine if we need to change button state
  buttonReading = digitalRead(DIGITAL_IN_PIN);

  if (buttonReading != buttonState) {
    lastChangeTime = millis();
  }

  // change the value if it's been pressed for long enough
  if ((millis() - lastChangeTime) > DEBOUNCE_DELAY) {
    if (buttonReading != buttonState) {
      buttonState = buttonReading;
    }
  }

  delay(RESET_TIME);
}
