#include <stdio.h>
#include <stdlib.h>

#include "sinetxt.h"

int main(int argc, char** argv) {

    if(argc != ARG_NARGS) {
        fprintf(stderr, "Usage: <bin_name> <nsamps> <freq> <srate>\n");
        return 1;
    }

    /* sintxt(atoi(argv[1]), atof(argv[2]), atof(argv[3])); */
    sintxt(atoi(argv[ARG_NSAMPS]), atof(argv[ARG_FREQ]), atof(argv[ARG_SR]));
    return 1;
}
