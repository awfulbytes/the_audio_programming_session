#include <stdio.h>
#include <math.h>

int main() {
    double c0, c5;
    int    midinote;
    // NOTE: 12 note octave tunning
    double semitone_r = pow(2.0, 1.0/12.0);
    double freq = 200.0;

    // NOTE: middle C is 3 semitones above low A (220)
    c5 = 200.0 * pow(semitone_r, 3.0);
    c0 = c5 * pow(0.5, 5.0);

    int fracmidi = log(freq / c0) / log(semitone_r);

    midinote = (int) (fracmidi + 0.5);

    printf("Nearest MIDI note to %f [Hz] is %d\n", freq, midinote);
}

// TODO: EXERSISE 1.2.5 is nice @p104 The Audio Programming Book
