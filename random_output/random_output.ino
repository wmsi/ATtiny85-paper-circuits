/*
 * random_output.ino
 * 
 * ATtiny85 Project
 * Randomly outputs on either pin 0, 1, or 2 when pin 3 or 4 goes high 
 * 
 * 12.28.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

// Pin defintions
const int SENSING_PIN_1 = 4;
//const int SENSING_PIN_2 = 3;

// (must be sequential and in increasing order)
const int OUTPUT_PIN_1 = 0;
const int OUTPUT_PIN_2 = 1;
const int OUTPUT_PIN_3 = 2;
const int OUTPUT_PIN_4 = 3;

const long DEBOUNCE_DELAY = 20; // ms to delay before actually reading input

// Variables
int state = 0;
int lastState = 0;

int lastReadState = 0;
long lastDebounceTime = 0;
int randPin = 0;

void setup() {
  // setup pins
  pinMode(SENSING_PIN_1, INPUT);
  //pinMode(SENSING_PIN_2, INPUT);
  
  pinMode(OUTPUT_PIN_1, OUTPUT);
  pinMode(OUTPUT_PIN_2, OUTPUT);
  pinMode(OUTPUT_PIN_3, OUTPUT);
  pinMode(OUTPUT_PIN_4, OUTPUT);
}

void loop() {
  // check whether either pin has just gone high
  if (digitalRead(SENSING_PIN_1) == HIGH) // || digitalRead(SENSING_PIN_2) == HIGH)
    state = HIGH;
  else
    state = LOW;

  // "start timer" if a state changes
  if (state != lastReadState)
    lastDebounceTime = millis();

  // if pin has been HIGH for long enough, check if it's actually changed
  if (millis() - lastDebounceTime > DEBOUNCE_DELAY)
  {
    if (lastState != state)
    {
      // only activate on LOW->HIGH; turn off on HIGH->LOW
      if (state == HIGH)
      {
        // choose a pin to output on based on a random number
        // (make sure the last one is included)
        randPin = random(OUTPUT_PIN_1, OUTPUT_PIN_4 + 1);
        digitalWrite(randPin, HIGH);
      }
      else
      {
        digitalWrite(OUTPUT_PIN_1, LOW);
        digitalWrite(OUTPUT_PIN_2, LOW);
        digitalWrite(OUTPUT_PIN_3, LOW);
        digitalWrite(OUTPUT_PIN_4, LOW);
      }

      // update the actual state for next iteration
      lastState = state;  
    }
  }

  // update the current state for next iteration
  lastReadState = state;
}
