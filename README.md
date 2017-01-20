#  ATtiny85-paper-circuits
These Arduino scripts are intended to be run on an [ATtiny85](https://www.sparkfun.com/products/9378) using the Arduino IDE and a [Tiny AVR Programmer](https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/). They were created as add-ons to paper circuits that would allow makers to integrate more complex functionality into their circuits, and even program the ATtiny85 themselves to create even more advanced functionality.

We have designed two kinds of boards to house the ATtiny85: a basic "LED Circuit" with only the chip and holder soldered on, and an "Audio Circuit" with a transistor and 9V connector to supply additional power to a speaker.

## Diagrams
Diagrams of the LED and Audio Circuits. These are the packages that would be added to a paper circuit.

## Paper Circuit Layouts
A series of printable layouts to serve as the starting point and guide for various paper circuits that correspond with particular programs or ATtiny85 circuits.

## Tutorial Diagrams
A series of diagrams intended for teachers or students, showing how to setup the ATtiny85 in a prescribed circuit, in particular for the Blink Series with Inputs and Audio Wizard programs.

## The Programs
The two following programs are for the LED (basic) Circuit and the Audio Circuit, respectively. The rest are for custom circuits and inspiration for further projects.

#### Audio Wizard
Creates various sounds, selected via several digital input pins. Also allows users to control properties of the sound with analog inputs.
#### Blink Series with Inputs
Cycles through all output pins from 0 to 2 in a series, creating a blinking series effect on LEDs, etc. arranged in a line. Also controls the speed of the blinking effect using an analog input, and the direction is toggled using a digital input.
#### Blink Series
Cycles through all output pins from 0 to 4 in a series, creating a blinking series effect on LEDs, etc. arranged in a line.
#### Fade
Fades output on all pins using an analog output sweep.
#### Fade Random
Fades output on all pins using an analog output sweep, but with random offsets for each pin.
#### Fade With Input
Fades output based on the value of an analog input.
#### Melody Selector
Using the functionality of Play Melody, plays different melodies based on an analog in reading (ex. a potentiometer) or digital in readings (as a binary input).
#### Note Scale
Using note indexes (vs. period values), plays the full note scale upwards in pitch and back down again.
#### Play Melody
Plays a simple melody by creating audio waveforms of certain frequencies (notes) out of square waves
#### Power Indicator
Uses a series of pins (with LEDs for example) to indicate the power level being applied to a certain input pin.
#### Program Selector
Runs different functions (representing other programs) based on an analog in reading (ex. a potentiometer controlling LED blink patterns)
#### Random Melody (Pentatonix)
Generates a random melody out of the Pentatonix note scale.
#### Random Noise
Randomly varies output on all pins
#### Random Output
Randomly outputs on one of several pins when a rising edge is detected on an input pin
#### Sine Wave
Outputs a sine wave voltage pattern on analog output (ex. to control an electromagnetic motor), with the frequency (i.e. period) of the wave determined by an analog input
#### Twinkle
Produces a star-like "twinkle" effect

**For more info contact us at http://www.whitemountainscience.org/**
