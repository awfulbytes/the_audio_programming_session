#include <math.h>
#include <stdio.h>

#include "expdecay.h"

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
