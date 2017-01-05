/*
 * play_melody.ino
 * 
 * ATtiny85 Project
 * Plays a simple melody by creating audio waveforms of 
 * certain frequencies (notes) out of square waves
 * 
 * 1.2.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

#define OUTPUT_PIN 0

// Define notes
// NOTE: Make sure you use these as LONGs on the ATtiny85! (w/ 16 bit ints)
// (A regular expression to manipulate these :) 
//  (\w\d)\s*((\d|\.)*)\s*((\d|\.)*) -> $1 $2 $4 )
//      NOTE  PERIOD // FREQ
#define C0  61162.08  // 16.35
#define D0  54495.91  // 18.35
#define E0  48543.69  // 20.60
#define F0  45808.52  // 21.83
#define G0  40816.33  // 24.50
#define A0  36363.64  // 27.50
#define B0  32393.91  // 30.87
#define C1  30581.04  // 32.70
#define D1  27240.53  // 36.71
#define E1  24271.84  // 41.20
#define F1  22909.51  // 43.65
#define G1  20408.16  // 49.00
#define A1  18181.82  // 55.00
#define B1  16196.95  // 61.74
#define C2  15288.18  // 65.41
#define D2  13620.27  // 73.42
#define E2  12134.45  // 82.41
#define F2  11453.44  // 87.31
#define G2  10204.08  // 98.00
#define A2  9090.91 // 110.00
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

// Melody
long notes[] = {G3, G3, G3, E3, B3, G3, E3, B3, G3, D4, D4, D4, E4, B3, G3, E3, B3,  R}; // {G4, G4, G4, E4, B4, G4, E4, B4, G4, D5, D5, D5, E5, B4, G4, E4, B4,  R};
int beats[] =  {16, 16, 16,  8,  8, 16,  8,  8, 32, 16, 16, 16,  8,  8, 16,  8,  8, 32};
int NUM_NOTES = sizeof(notes) / sizeof(long);

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
  playMelody(notes, beats, NUM_NOTES);
}

/**
 * Plays a series of notes using playNote() given an array 
 * of note periods and an array of note beat durations.
 */
void playMelody(long* notes, int* beats, int numNotes) {
  for (int i = 0; i < numNotes; i++)
  {
    long playDuration = beats[i] * BEAT_DURATION;

    // handle rests differently
    if (notes[i] > 0)
      playNote(notes[i], playDuration);
    else
      delayMicroseconds(playDuration);

    delayMicroseconds(INTER_NOTE_REST);
  }
}

/* Plays a note of the given uS period (i.e. freq) for the given uS duration 
 * NOTE: Durations on the microsecond level are not very accurate
 * (there's a lot of overhead) so there may be frequency, etc. limits to this method.
 */
void playNote(long period, long duration)
{
  long elapsedDuration = 0;
  while (elapsedDuration < duration)
  {
    // generate approximate sine wave (actually a square wave)
    digitalWrite(OUTPUT_PIN, HIGH);
    delayMicroseconds(period / 2);

    digitalWrite(OUTPUT_PIN, LOW);
    delayMicroseconds(period / 2);

    elapsedDuration += period;
  }
}

