#include <math.h>
#include "maxsamp.h"

double maxsamp(float *buf, unsigned long blocksize){
    double absval, peak = 0.0;
    unsigned long i;

    for (i=0; i < blocksize; i++){
        absval = fabs(buf[i]);
        if (absval > peak){
            peak = absval;
        }
    }
    return peak;
}
