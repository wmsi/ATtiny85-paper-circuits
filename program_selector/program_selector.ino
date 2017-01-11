/*
 * program_selector.ino
 * 
 * ATtiny85 Project
 * Runs different functions (representing other programs) based on an analog in reading 
 * (ex. a potentiometer controlling LED blink patterns)
 * 
 * 12.29.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

#define NUM_OPTIONS 5 // number of programs options (# of sections to divide input range into)
#define SELECTOR_PIN A2 // analog input
#define LOWEST_INPUT 0 // minimum analog input 
#define HIGHEST_INPUT 1023 // max analog input (represents min/max of whatever resistive device)

#define NUM_PINS 4

int reading = 0, selector = 0;

void setup() {
  pinMode(SELECTOR_PIN, INPUT);
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  reading = analogRead(SELECTOR_PIN);

  // convert the analog reading to a function index corresponding to one of our functions
  selector = map(reading, LOWEST_INPUT, HIGHEST_INPUT, 0, NUM_OPTIONS);

  // based on selector value, run a different function (should go up to NUM_OPTIONS)
  switch (selector) 
  {
    case 0:
      blink_series();
      break;
    case 1:
      random_noise();
      break;
    case 2: 
      fade();
      break;
    case 3:
      twinkle();
      break;
    case 4:
      // RGB LED????
      break;
    default:
      // indicates some input error
      blinky();
      break;
  }
}

/**
 * Blinks all outputs in a series from pin 0 to 4
 */
void blink_series() {
  // CONSTANTS
  #define BLINK_TIME 400 // ms; duration light is on for
  #define RESET_TIME 0 // ms; duration to wait before looping again

  // go through all pins, blinking each on and off briefly
  for (int i = 0; i < NUM_PINS; i++) {    
    digitalWrite(i, HIGH);
    delay(BLINK_TIME);
    digitalWrite(i, LOW);
  }   

  delay(RESET_TIME);
}

/**
 * Randomly varies output on all pins
 */
void random_noise() {
  // Constants
  #define RESET_TIME 200 // ms; duration to wait before getting new random values

  // write a random voltage to each pin
  // Note: becasue only 3 out of 5 pins support analog output (PWM), 
  // the digital pins will just be either on or off based on this value
  for (int i = 0; i < NUM_PINS; i++) {
    analogWrite(i, random(0, 255));
  }  
  delay(RESET_TIME);
}

/** 
 * Produces a star-like "twinkle" effect 
 */
void twinkle() {
  // Constants
  const int FADE_DELAY = 10; // ms; controls fade speed 
                          // defined as variable becasue another function uses FADE_DELAY)
  #define UPPER_BRIGHTNESS 255
  #define LOWER_BRIGHTNESS 100  

  // gradually increase brightness in the range for all pins
  for (int i = LOWER_BRIGHTNESS; i < UPPER_BRIGHTNESS; i++) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, i);
    }
    delay(FADE_DELAY);
  } 
  
  // gradually decrease brightness in the range for all pins
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

/**
 * Fades the output on all pins from off to full power
 * Note: digital pins will just blink
 */
void fade() {
  // Constants
  const int FADE_DELAY = 8; // ms; controls fade speed
                            // defined as variable becasue another function uses FADE_DELAY)
  
  // gradually increase brightness for all pins
  for (int i = 0; i < 255; i++) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, i);
    }
    delay(FADE_DELAY);
  } 
  
  // gradually decrease brightness for all pins
  for (int i = 255; i > 0; i--) {
    for (int pin = 0; pin < NUM_PINS; pin++) {
      analogWrite(pin, i);
    }
    delay(FADE_DELAY);
  }
}

// Blinks first output (used as a diagnostic)
void blinky() {
  digitalWrite(0, HIGH);
  delay(500); 
  digitalWrite(0, LOW);    
  delay(500);                       
}

