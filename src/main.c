#include "expdecay.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {

    if (argc < 4) {
        printf("usage: <bin_name> <duration> <T> <steps>\n");
        return 1;
    }

    /* dur    = atof(argv[1]); */
    /* T      = atof(argv[2]); */
    /* NOTE: steps are always int values bruh */
    /* nsteps = atoi(argv[3]); */

    expdecay(atof(argv[1]),  atof(argv[2]), atoi(argv[3]));
    return 0;
}
