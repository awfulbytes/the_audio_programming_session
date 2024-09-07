#include <stdio.h>

short samp = (short) (0.5 * 32767);
short samp2 = (short) 0.5 * 32767;

void cast() {
    printf("%d\n", samp);
    printf("%d\n", samp2);
}
