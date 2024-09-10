#include <math.h>
#include <stdio.h>

#include "expdecay.h"

/**
* Creating an exponential decay curve.
*
* Using pure math logic to generate the points of an exponential decay function
* from 0 to 1 (normalized values).
*
** double dur The duration in seconds of the decay.
** double T   The period i thing ... TODO: see what the hell is that.
** int nsteps The number of points consisting the curve (resolution).
*
* @return Just print to stdout the values (usefull for creating breakpoint
*         files)
*/
void expdecay(double dur, double T, int nsteps){
    int i;

    // NOTE: k is the constant time increment
    //       a is the constant ratio value
    //       x is the starting decay value
    double step = 0.0, x = 1.0, a, k;

    k = dur / nsteps;
    a = exp(-k/T);

    for(i = 0; i < nsteps; i++){
        printf("%.4lf\t%.8lf\n", step, x);
        x = a * x;
        step += k;
    }
}
