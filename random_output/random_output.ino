/*
 * random_output.ino
 * 
 * ATtiny85 Project
 * Randomly outputs on one of several pins when a rising edge is detected on an input pin
 *  
 * 12.28.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

// Constants
#define SENSING_PIN_1 4
#define NUM_PINS 4
#define DEBOUNCE_DELAY 20 // ms to delay before actually reading input

// Variables
int randPin = 0;
int state = 0;

// needed for debouncing
int lastState = 0;
int lastReadState = 0;
long lastDebounceTime = 0;

void setup() {
  // setup pins
  pinMode(SENSING_PIN_1, INPUT);

  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // get digital input reading
  state = digitalRead(SENSING_PIN_1);

  // use debouncing so that we don't pay attention to changes in the button
  // state unless they stay that way for longer than DEBOUNCE_DELAY
  // (see https://www.arduino.cc/en/Tutorial/Debounce for more info)

  // "start timer" if a state changes
  if (state != lastReadState)
    lastDebounceTime = millis();

  // if pin has been HIGH for long enough, check if it's actually changed
  if (millis() - lastDebounceTime > DEBOUNCE_DELAY)
  {
    // if it hasn't changed we don't need to activate
    if (lastState != state)
    {
      // only activate on LOW->HIGH; turn off on HIGH->LOW
      if (state == HIGH)
      {
        // choose a pin to output on based on a random number
        // (make sure the last one is included)
        randPin = random(0, NUM_PINS + 1);
        digitalWrite(randPin, HIGH);
      }
      else
      {
        // turn off all the pins
        for (int i = 0; i < NUM_PINS; i++) {
          digitalWrite(i, LOW);
        }
      }

      // update the actual state for the next iteration
      lastState = state;  
    }
  }

  // update the current state reading for the next iteration
  lastReadState = state;
}

/* Code to use multiple input pins
  #define SENSING_PIN_2 3 
   
  pinMode(SENSING_PIN_2, INPUT);

  ...
 
  // check whether either pin has just gone high
  if (digitalRead(SENSING_PIN_1) == HIGH) // || digitalRead(SENSING_PIN_2) == HIGH)
    state = HIGH;
  else
    state = LOW;
*/
