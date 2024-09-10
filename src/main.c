#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "sinetxt.h"
#include <portsf.h>

int main(int argc, char** argv) {

    if(argc != ARG_NARGS) {
        fprintf(stderr, "Usage: <bin_name> <outfile>.txt <dur> <freq> <srate> <amp>\n");
        return 1;
    }



    int i, sr, nsamps;
    double samp, dur, freq, srate, amp, maxsamp;
    double twopi = 2.0 * M_PI;
    double start, end, fac, angleincr;
    FILE* fp = NULL;

    fp = fopen(argv[ARG_OUTFILE], "w");
    if(fp == NULL){
        fprintf(stderr, "Error creating the output file %s\n", argv[ARG_OUTFILE]);
        return 1;
    }

    dur = atof(argv[ARG_DUR]);
    freq = atof(argv[ARG_HZ]);
    srate = atof(argv[ARG_SR]);
    amp = atof(argv[ARG_AMP]);
    nsamps = (int) (dur * srate);
    angleincr = twopi * freq / srate;

    start = 1.0;
    end = 1.0e-4;
    maxsamp = 0.0;
    fac = pow(end/start, 1.0/nsamps);

    for(i = 0; i < nsamps; i++){
        samp = amp * sin(angleincr * i);
        samp *= start;
        start *= fac;
        fprintf(fp, "%.8lf\n", samp);

        if(fabs(samp) > maxsamp){
            maxsamp = fabs(samp);
        }
    }
    fclose(fp);
    fprintf(stdout, "done. Max sample value = %.8lf\n", maxsamp);
    return 1;
}
