/*
 * program_selector.ino
 * 
 * ATtiny85 Project
 * Runs different functions (representing other programs) based an analog in reading 
 * (ex. a potentiometer controlling LED blink patterns)
 * 
 * 12.29.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

const int NUM_OPTIONS = 5; // number of programs options (# of sections to divide input range into)
const int SELECTOR_PIN = A2; // analog input
const int LOWEST_INPUT = 0; // minimum analog input 
const int HIGHEST_INPUT = 1023; // max analog input (represents min/max of whatever resistive device)

const int NUM_PINS = 4;

int reading = 0, selector = 0;

void setup() {
  pinMode(SELECTOR_PIN, INPUT);
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  reading = analogRead(SELECTOR_PIN);

  // convert the analog reading to a function index
  selector = map(reading, LOWEST_INPUT, HIGHEST_INPUT, 0, NUM_OPTIONS);

  // based on selector value, run a different function (should go up to NUM_OPTIONS)
  switch (selector) 
  {
    case 0:
      blink_series();
      break;
    case 1:
      random_output();
      break;
    case 2: 
      twinkle();
      break;
    case 3:
      fade();
      break;
    case 4:
      //play_melody();
      break;
    default:
      blinky();
      break;
  }
}

// Blinks all outputs in a series from pin 0 to 4
void blink_series() {
  // CONSTANTS
  const long BLINK_TIME = 400; // ms; duration light is on for
  const long RESET_TIME = 0; // ms; duration to wait before looping again
  
  for (int i = 0; i < NUM_PINS; i++) {    
    digitalWrite(i, HIGH);
    delay(BLINK_TIME);
    digitalWrite(i, LOW);
  }   

  // shut off all pins to reset
//  for (int i = 0; i < NUM_PINS; i++) {    
//    digitalWrite(i, LOW);
//  }

  delay(RESET_TIME);
}

// Randomly varies output on all pins
void random_output() {
  // Constants
  const long RESET_TIME = 200; // ms; duration to wait before getting new random values

  for (int i = 0; i < NUM_PINS; i++) {
    // write a random voltage
    analogWrite(i, random(0, 255));
  }  
  delay(RESET_TIME);
}

// Produces a star-like "twinkle" effect
void twinkle() {
  // Constants
  const long FADE_DELAY = 10; // ms; controls fade speed
  const long UPPER_BRIGHTNESS = 255;
  const long LOWER_BRIGHTNESS = 100;  

  // increase output
  for (int i = LOWER_BRIGHTNESS; i < UPPER_BRIGHTNESS; i++) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, i);
    }
    delay(FADE_DELAY);
  } 
  
  // decrease output
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

void fade() {
  // Constants
  const int FADE_DELAY = 8; // ms; controls fade speed
  
  // increase output
  for (int i = 0; i < 255; i++) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, i);
    }
    delay(FADE_DELAY);
  } 
  
  // decrease output
  for (int i = 255; i > 0; i--) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, i);
    }
    delay(FADE_DELAY);
  }
}

// Blinks first output (used as a diagnostic
void blinky() {
  digitalWrite(0, HIGH);
  delay(500); 
  digitalWrite(0, LOW);    
  delay(500);                       
}

