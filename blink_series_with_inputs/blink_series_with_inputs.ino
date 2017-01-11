/*
 * blink_series_with_inputs.ino
 * 
 * ATtiny85 Project
 * Cycles through all output pins from 0 to 2 in a series, 
 * creating a blinking series effect on LEDs, etc. arranged in a line.
 * Also controls the speed of the blinking effect using an analog input, 
 * and the direction is toggled using a digital input.
 * 
 * 12.28.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

#define DIGITAL_IN_PIN 3
#define ANALOG_IN_PIN A2
#define NUM_PINS 3

#define MIN_BLINK_TIME 30 // ms; min duration light is on for
#define MAX_BLINK_TIME 450 // ms; max duration light is on for

#define LOWEST_INPUT 0 // input that should be min blink speed
#define HIGHEST_INPUT 1023 // input that should be max blink speed 

#define RESET_TIME 2 // ms; duration to wait before looping again

// variables
int input = 0; 
long blinkTime = 0; // variable duration light is on for
int buttonState = HIGH;

void setup() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(ANALOG_IN_PIN, INPUT);
  pinMode(DIGITAL_IN_PIN, INPUT);
}

void loop() {
  input = analogRead(ANALOG_IN_PIN);

  // invert input to have the SLOW blinking be the default
  input = HIGHEST_INPUT - input;

  // convert analog input to a blink duration
  blinkTime = map(input, LOWEST_INPUT, HIGHEST_INPUT, MIN_BLINK_TIME, MAX_BLINK_TIME);

  buttonState = digitalRead(DIGITAL_IN_PIN);

  // execute blink series (we may be going either direction)
  for (int i = 0; i < NUM_PINS; i++) {
    // determine direction based on digital input
    int blinkPin = i;
    if (buttonState == HIGH)
      // if button pressed (pulled HIGH), convert the first pin to the last,
      // second to second to last, etc. so that it blinks in the other direction
      blinkPin = NUM_PINS - 1 - i;
    
    digitalWrite(blinkPin, HIGH);
    delay(blinkTime);
    digitalWrite(blinkPin, LOW);
  }

  delay(RESET_TIME);
}


// DEPRECATED DEBOUNCING (not really needed here; really only causes trouble)
/*
  #define DEBOUNCE_DELAY 20
  int buttonReading = HIGH;
  int lastChangeTime = 0;
  
  ...
 
  // determine if we need to change button state
  // buttonReading = digitalRead(DIGITAL_IN_PIN);
  
  if (buttonReading != buttonState) {
    lastChangeTime = millis();
  }
  
  // change the value if it's been pressed for long enough
  if ((millis() - lastChangeTime) > DEBOUNCE_DELAY) {
    if (buttonReading != buttonState) {
      buttonState = buttonReading;
    }
  }
*/
