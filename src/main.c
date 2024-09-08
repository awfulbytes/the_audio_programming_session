#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
    int i, nsteps;

    // NOTE: k is the constant time increment
    //       a is the constant ratio value
    //       x is the starting decay value
    double step, x, a, T, k;
    double dur;

    if (argc < 4) {
        printf("usage: <bin_name> <duration> <T> <steps>\n");
        return 1;
    }

    dur    = atof(argv[1]);
    T      = atof(argv[2]);
    // NOTE: steps are always int values bruh
    nsteps = atoi(argv[3]);

    k = dur / nsteps;
    a = exp(-k/T);
    x = 1.0;

    step = 0.0;
    for (i = 0; i < nsteps; i++) {
        printf("%.4lf\t%.8lf\n", step, x);
        x = a * x;
        step += k;
    }
    return 0;
}
