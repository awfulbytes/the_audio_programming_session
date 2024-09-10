#include "expbrk.h"
#include <math.h>
#include <stdio.h>

void expbrks(double dur, int npoints, double startval, double endval){
    int i;
    double thisstep, start, end;
    double frac, valrange, offset;
    const double verysmall = 1.0e-4;   /*< -80dB*/

    if (dur <= 0.0){
        fprintf(stderr, "Error: duration must be positive always and >1.\n");
    }

    if (npoints <= 0){
        fprintf(stderr, "Error: number of steps cannot be less than 1\n");
    }

    double step = dur / npoints;
    valrange = endval - startval ;
    if (valrange == 0.0){
        fprintf(stderr, "Warning: start and end values are the same!\n");
    }
    if (valrange < 0.0) {
        start = 1.0;
        end = verysmall;
        valrange = -valrange;
        offset = endval;
    }
    else {
        start = verysmall;
        end = 1.0;
        offset = startval;
    }

    thisstep = 0.0;
    /* normalized curve construction.. scale out to inp values (range) */
    frac = pow(end/start, 1.0/npoints);
    for (i = 0; i < npoints; i++){
        fprintf(stdout, "%.4lf\t%.8lf\n", thisstep, offset + (start * valrange));
        start *= frac;
        thisstep += step;
    }
    fprintf(stderr, "DONE\n");
}
