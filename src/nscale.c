#include <stdio.h>
#include "nscale.h"

void zero_filler(double buffer[1024]){
    // NOTE: the best way to fill a buffer with zeros
    // NOTE: This would be read as ‘‘set the contents of ptr to 0.0, then
    // increment ptr.’’
    double* ptr;
    for (int i = 0; i < 1024; i++)
        *ptr++ =0.0;
}

void scaler(int notes_amount, int midi_note) {
    double frequency, ratio;
    double c0, c5;
    ratio = pow(2.0, 1.0 / 12.0);

    // NOTE: find middle C 3 semitones above low A = 220 Hz
    c5 = 220.0 * pow(ratio, 3.0);

    // NOTE: moving 5 octaves bellow C5 (middle C) to find C base (first octave)
    c0 = c5 * pow(0.5, 5.0);

    // NOTE: calculate the frequency using offseting the note from the base C(0)
    frequency = c0 * pow(ratio, midi_note);

    double freaqs[24];
    double intervals[24];
    // NOTE: need to recalculate the ratio given the number of notes to devide
    // the octave but the C5 and C0 need the 12 note devision in order to have
    // the default boundaries and not going out of the octave range when having
    // a ratio > 12. No need for checking bellow this limit.
    ratio = pow(2.0, 1.0 / notes_amount);

    for (int i = 0; i < notes_amount; i++){
        intervals[i] = frequency;
        frequency *= ratio;
    }

    for (int i = 0; i < notes_amount; i++){
        printf("%d,\t frequencies: %.2f\n", i, intervals[i]);
    }
}
