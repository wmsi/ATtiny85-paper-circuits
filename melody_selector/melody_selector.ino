/*
 * melody_selector.ino
 * 
 * ATtiny85 Project
 * Using the functionality of play_melody, plays different melodies  
 * based on an analog in reading (ex. a potentiometer) or digital in
 * readings (as a binary input)
 * 
 * 1.2.2016
 * Mckenna Cisler
 * White Mountain Science, Inc.
 */

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

#define OUTPUT_PIN 0
#define NUM_OPTIONS 5 // number of  melody options (# of sections to divide input range into)

//#define USE_ANALOG_SELECTOR // uncomment to use binary digital selector
#ifdef USE_ANALOG_SELECTOR
  #define SELECTOR_PIN A2 // analog input
#else
  #define SELECTOR_PIN_1 1 // pins to select program  // ones bit
  #define SELECTOR_PIN_2 2                            // twos bit 
#endif


#define LOWEST_INPUT 0 // minimum analog input 
#define HIGHEST_INPUT 1023 // max analog input (represents min/max of whatever resistive device)

// Tempos
#define BEAT_DURATION   40000  // uS - how long a single beat is
#define INTER_NOTE_REST 10000 // uS - how long to rest between each note
                                // (this is done because it's easier to hear notes)

// Melodies
// Imperial March - http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0017607
long notes_imperial_march[] = {G3, G3, G3, E3, B3, G3, E3, B3, G3, D4, D4, D4, E4, B3, G3, E3, B3,  R};
int8_t beats_imperial_march[] =  {16, 16, 16,  8,  8, 16,  8,  8, 32, 16, 16, 16,  8,  8, 16,  8,  8, 32};
int num_notes_imperial_march = sizeof(notes_imperial_march) / sizeof(long);

// Mary had a Little Lamb - http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0127902
long notes_mary_lamb[] = {A3, G3, F3, G3, A3, A3, A3, G3, G3, G3, A3, C4, C4}; 
int8_t beats_mary_lamb[] =  { 8,  8,  8,  8,  8,  8, 16,  8,  8, 16,  8,  8, 16};
int num_notes_mary_lamb = sizeof(notes_mary_lamb) / sizeof(long);

// Raiders March - http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0130280
long notes_raiders[] =   {E4, F4, G4, C5, D4, E4, F4,  R, G4, A4, B4, F5, A4, B4, C5, D5, E5};
int8_t beats_raiders[] = { 4,  4,  4, 24,  4,  4, 16,  8,  4,  4,  4, 24,  4,  4,  8,  8,  8};
int num_notes_raiders = sizeof(notes_raiders) / sizeof(long);

// Twinkle Twinkle Little Star - http://makingmusicfun.net/pdf/sheet_music/twinkle-twinkle-little-star-piano-solo.pdf
long notes_twinkle[] = {C5, C5, G5, G5, A5, A5, G5, F5, F5, E5, E5, D5, D5, C5, R};
int8_t beats_twinkle[] =  {16, 16, 16, 16, 16, 16, 32, 16, 16, 16, 16, 16, 16, 32, 32};
int num_notes_twinkle = sizeof(notes_twinkle) / sizeof(long);

// Old Macdonald had a Farm - http://makingmusicfun.net/pdf/sheet_music/old-macdonald-piano-solo.pdf
long notes_macdonald[] = {G4, G4, G4, D4, E4, E4, D4, B4, B4, A4, A4, G4, D4};
int8_t beats_macdonald[] =  { 8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8, 16,  8};
int num_notes_macdonald = sizeof(notes_macdonald) / sizeof(long);

// Carol of the Bells (short) - http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0060566
long notes_carol[] = {G5, F5, G5, E5};
int8_t beats_carol[] =  { 8,  4,  4,  8};
int num_notes_carol = sizeof(notes_carol) / sizeof(long);

// Pirates of the Carribean - http://easymusicnotes.com/index.php?option=com_content&view=article&id=1588:pirates-of-the-caribbean-theme&catid=148:piano-level-4&Itemid=155
long notes_pirates[] =    { R, A2_, C3, D3, D3,  R, D3, E3, F3, F3,  R, F3, G3, E3, E3,  R, D3, C3, D3}; 
int8_t beats_pirates[] =  {16,  8,  8, 16, 16, 16,  8,  8, 16, 16, 16,  8,  8, 16, 16, 16,  8,  8, 16};
int num_notes_pirates = sizeof(notes_pirates) / sizeof(long);

// Variables
int selector = 0;
#ifdef USE_ANALOG_SELECTOR
  int reading = 0;
#else
  int selectorVal1 = 0, selectorVal2 = 0;
#endif

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);

  #ifdef USE_ANALOG_SELECTOR
    pinMode(SELECTOR_PIN, INPUT);
  #else
    pinMode(SELECTOR_PIN_1, INPUT);
    pinMode(SELECTOR_PIN_2, INPUT);
  #endif
}

void loop() {
  #ifdef USE_ANALOG_SELECTOR
    reading = analogRead(SELECTOR_PIN);
    
    // convert the analog reading to a function index
    selector = map(reading, LOWEST_INPUT, HIGHEST_INPUT, 0, NUM_OPTIONS);
  #else
    // get pin values, adding debouncing
    selectorVal1 = digitalRead(SELECTOR_PIN_1);
    selectorVal2 = digitalRead(SELECTOR_PIN_2);

    // generate selector out of pin values (treat as bits)
    selector = 2 * selectorVal2 + selectorVal1;
  #endif 
  
  // based on selector value, run a different function (should go up to NUM_OPTIONS)
  switch (selector) 
  {
    case 0:
      playMelody(notes_imperial_march, beats_imperial_march, num_notes_imperial_march);
      break;
    case 1:
      playMelody(notes_mary_lamb, beats_mary_lamb, num_notes_mary_lamb);
      break;
    case 2: 
      playMelody(notes_twinkle, beats_twinkle, num_notes_twinkle);
      break;
    case 3:
      playMelody(notes_macdonald, beats_macdonald, num_notes_macdonald);
      break;
    case 4:
      playMelody(notes_raiders, beats_raiders, num_notes_raiders);
      //playMelody(notes_carol, beats_carol, num_notes_carol);
      //playMelody(notes_pirates, beats_pirates, num_notes_pirates);
      break;
    default:
      playNote(C3, BEAT_DURATION * 8);
      break;
  }  
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
    // generate approximate sine wave (actually a square wave)
    digitalWrite(OUTPUT_PIN, HIGH);
    delayMicroseconds(period / 2);

    digitalWrite(OUTPUT_PIN, LOW);
    delayMicroseconds(period / 2);

    elapsedDuration += period;
  }
}

/*
void noteSweep() {
  for (long i = B8; i < C1; i += 100) {
    playNote(i, BEAT_DURATION / 2);
  }
}
*/
