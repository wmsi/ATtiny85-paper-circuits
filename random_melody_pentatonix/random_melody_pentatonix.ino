/*
 * random_melody_pentatonix.ino
 * 
 * ATtiny85 Project
 * Generates a random melody out of the Pentatonix note scale.
 * 
 * 1.19.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

#define e 2.718281828 // the fundamental constant

#define OUTPUT_PIN 0

// Define notes
// NOTE: Make sure you use these as LONGs on the ATtiny85! (it has only 16 bit ints)
// (A regular expression to manipulate these :) 
//  (\w\d)\s*((\d|\.)*)\s*((\d|\.)*) -> $1 $2 $4 )
//    NOTE  PERIOD (uS) // FREQ (Hz)
#define C0  61162.08  // 16.35
#define D0  54495.91  // 18.35
#define E0  48543.69  // 20.60
#define F0  45808.52  // 21.83
#define G0  40816.33  // 24.50
#define A0_  36363.64  // 27.50 // Make sure we don't interfere with analog pins
#define B0  32393.91  // 30.87
#define C1  30581.04  // 32.70
#define D1  27240.53  // 36.71
#define E1  24271.84  // 41.20
#define F1  22909.51  // 43.65
#define G1  20408.16  // 49.00
#define A1_  18181.82  // 55.00
#define B1  16196.95  // 61.74
#define C2  15288.18  // 65.41
#define D2  13620.27  // 73.42
#define E2  12134.45  // 82.41
#define F2  11453.44  // 87.31
#define G2  10204.08  // 98.00
#define A2_  9090.91 // 110.00
#define B2  8099.13 // 123.47
#define C3  7644.68 // 130.81
#define D3  6810.60 // 146.83
#define E3  6067.59 // 164.81
#define F3  5727.05 // 174.61
#define G3  5102.04 // 196.00
#define A3  4545.45 // 220.00
#define B3  4049.57 // 246.94
#define C4  3822.19 // 261.63
#define D4  3405.30 // 293.66
#define E4  3033.70 // 329.63
#define F4  2863.44 // 349.23
#define G4  2551.02 // 392.00
#define A4  2272.73 // 440.00
#define B4  2024.78 // 493.88
#define C5  1911.13 // 523.25
#define D5  1702.62 // 587.33
#define E5  1516.88 // 659.25
#define F5  1431.72 // 698.46
#define G5  1275.53 // 783.99
#define A5  1136.36 // 880.00
#define B5  1012.38 // 987.77
#define C6  955.57  // 1046.50
#define D6  851.31  // 1174.66
#define E6  758.43  // 1318.51
#define F6  715.87  // 1396.91
#define G6  637.76  // 1567.98
#define A6  568.18  // 1760.00
#define B6  506.19  // 1975.53
#define C7  477.78  // 2093.00
#define D7  425.66  // 2349.32
#define E7  379.22  // 2637.02
#define F7  357.93  // 2793.83
#define G7  318.88  // 3135.96
#define A7  284.09  // 3520.00
#define B7  253.10  // 3951.07
#define C8  238.89  // 4186.01
#define D8  212.83  // 4698.63
#define E8  189.61  // 5274.04
#define F8  178.97  // 5587.65
#define G8  159.44  // 6271.93
#define A8  142.05  // 7040.00
#define B8  126.55  // 7902.13

// "Rest" note
#define R   0 

// Tempos
long BEAT_DURATION =   40000;  // uS - how long a single beat is
long INTER_NOTE_REST = 10000; // uS - how long to rest between each note
                                // (this is done because it's easier to hear notes)

// The Pentatonix scale is a series of note ratios that (by the magic of music theory)
// tend to sound good together in any order.
// These are a series of notes that follow those ratios.
// For more see https://en.wikipedia.org/wiki/Pentatonic_scale
long pentatonix_scale[] = {A4, C5, D5, E5, G5, A5};
const int NUM_PENTATONIX = 6;

#define MELODY_LEN 18 // length of random melody to play
#define BEATS_PER_NOTE 16

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
  for (int i = 0; i < MELODY_LEN; i++)
  {
    // get a random note by generating a random index and using it
    // to grab one at random from the list
    long randomNote = pentatonix_scale[random(0, NUM_PENTATONIX)];

    // play the note at a constant duration
    playNote(randomNote, BEATS_PER_NOTE * BEAT_DURATION);

    delayMicroseconds(INTER_NOTE_REST);
  }

  // reset after each melody
  //delay(500);
}

/**
 * Plays a note of the given uS period (i.e. freq) for the given uS duration 
 * NOTE: Durations on the microsecond level are not very accurate
 * (there's a lot of overhead) so there may be frequency, etc. limits to this method.
 */
void playNote(long period, long duration)
{
  long elapsedDuration = 0;
  while (elapsedDuration < duration)
  {
    // to make a certain note, generate approximate sine wave (actually a square wave)
    // of the right frequency by going HIGH for half a period, and low for half a period:
    //     1 period
    //   <----------->
    //  |------|
    //  | HIGH |
    //         | LOW  |
    //         |------|
    digitalWrite(OUTPUT_PIN, HIGH);
    delayMicroseconds(period / 2);

    digitalWrite(OUTPUT_PIN, LOW);
    delayMicroseconds(period / 2);

    elapsedDuration += period;
  }
}

