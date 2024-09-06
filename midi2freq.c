#include <stdio.h>
// NOTE: To use math.h complex.h fenv.h -lm should be passed to the gcc flags
#include <math.h>

int low_A = 440.0/2.0;

int main() {
    // middle C5 and base note (below human hearing)
    double c0, c5;
    int    midinote;
    // NOTE: 12 note octave tunning
    double semitone_r = pow(2.0, 1.0/12.0);

    // NOTE: middle C is 3 semitones above low A (220)
    c5 = low_A * pow(semitone_r, 3.0);
    c0 = c5 * pow(0.5, 5.0);

    midinote = 73;
    double freq = c0 * pow(semitone_r, midinote);

    // NOTE: %.xf where x is int defines the decimal presizion
    printf("Midi note %d has frequency %.2f [Hz]\n", midinote, freq);
    return 0;
}
