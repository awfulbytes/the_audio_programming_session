#include <stdio.h>
#include <math.h>

#include "sinetxt.h"

/* #define DEBUG -DDEBUG */

void sintxt(int nsamps, double freq, double srate){
    int i;
    double sampl;
    double twopi = 2.0 * M_PI;
    double angleincrmnt;

    angleincrmnt = twopi * (freq / srate);
    #ifdef DEBUG
    printf("two*pi = %lf\t", twopi);
    printf("freque = %lf\t", freq);
    printf("sampling rate = %lf\n", srate);
    #endif

    for (i = 0; i < nsamps; i++){
        sampl = sin(angleincrmnt*i);

        #ifndef DEBUG
        fprintf(stdout, "%.8lf\n", sampl);
        #endif

        #ifdef DEBUG
        fprintf(stdout, "DBG: Sine Ampl: %.8lf\tangleincr %lf\n", sampl, angleincrmnt);
        #endif
    }
    fprintf(stderr, "DONE!!\n");
}
