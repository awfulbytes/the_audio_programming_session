#include <stdio.h>
#include <string.h>

int mod12(int note) {
    while (note < 0) note +=12;
    while (note >= 12) note -=12;
    return note;
}


int main() {
    char note[3], **p1, **p2,
        *table[12] = {"C", "C#", "D", "D#",
                    "E", "F", "F#", "G",
                    "G#", "A", "A#", "B"};
    // place pointers at start and end of the table
    p1 = table;
    p2 = table+11;

    printf("Enter base note (Capitals and # for sharps, 'A#'): ");
    scanf("%s", note);

    // find base note by incrementing the pointer1 comparing with the p2 (end).
    while (strcmp(*p1, note)) {
        p1++;
        if (p1 > p2) {
            printf("\nCould not match %s with any known note\n", note);
            printf("We represent notes in an octave as: \n");

            int i;
            for (i=0; i <= 11; i++)
                printf("%s  ", table[i]);
            return 1;
        }
    }

    int interval;
    printf("Enter interval in semitones: ");
    scanf("%d", &interval);

    // add the interval to the base note address
    p1 += mod12(interval);
    if (p1 > p2) {
        p1 -=12;
    }
    printf("%s transposed by %d semitones is %s\n", note, interval, *p1);
    return 0;
}
