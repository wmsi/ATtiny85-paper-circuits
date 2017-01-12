/*
 * sine_wave.ino
 * 
 * ATtiny85 Project
 * Outputs a sine wave voltage pattern on analog output (ex. to control an electromagnetic motor), 
 * with the frequency (i.e. period) of the wave determined by an analog input
 * 
 * 1.11.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

#define OUTPUT_PIN 0
#define ANALOG_IN_PIN A2

#define LOWEST_INPUT 0 // input that should be min period
#define HIGHEST_INPUT 1023 // input that should be max period

#define MIN_PERIOD 40 // 20 // ms; min period of sine wave
#define MAX_PERIOD 4000 // 4000 // ms; max period of sine wave

#define WAVE_MAGNITUDE 127.0 // max 127 (because wave goes from 0 to WAVE_MAGNITUDE * 2) (should be a long too)
#define LOOP_DELAY 2 // ms; how long to delay each loop (approx. equal to "sample rate")

long t = 0; // time progress in wave
long period = 0; // period of the sine wave to generate
long loopStartTime = 0; // time loops starts to we can measure execution time

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(ANALOG_IN_PIN, INPUT);
}

void loop() {
  // log the start time
  loopStartTime = millis();

  // modify period with analog input
  //int input = analogRead(ANALOG_IN_PIN);

  // convert the analog value to a period value
  period = MAX_PERIOD; // map(input, LOWEST_INPUT, HIGHEST_INPUT, MIN_PERIOD, MAX_PERIOD); 

  // get the value of the sine wave at this point in time by
  // multiplying the standard period (2pi) by the progress towards a complete TIME
  // period (t / period)
  // Also shift up so that the value is never negative
  int valueHere = WAVE_MAGNITUDE * sin((2*PI) * ((float) t / (float) period)) + WAVE_MAGNITUDE;

  // set that value now
  analogWrite(OUTPUT_PIN, valueHere);

  delay(LOOP_DELAY);

  // increment time, wrapping around to avoid overflow
  t = (t + (millis() - loopStartTime)) % period;
}
