#ifndef BRKPNT_H_
#define BRKPNT_H_
#include <stdio.h>

typedef struct breakpoint {
    double time;
    double value;
} brkpnt_t;

brkpnt_t* get_brkpnts(FILE* fp, long* psize);
brkpnt_t maxpoint(const brkpnt_t* points, long npoints);

#endif // BRKPNT_H_
