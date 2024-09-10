#include <stdio.h>
#include <stdlib.h>
#include "brkpnt.h"

long size = 0;
brkpnt_t* points;

brkpnt_t* get_brkpnts(FILE* fp, long* psize){
    int got;
    long npoints = 0, size = 64;
    double lasttime = 0.0;
    brkpnt_t* points = NULL;
    char line[80];

    if(fp == NULL)
        return NULL;

    points = (brkpnt_t*) malloc(sizeof(brkpnt_t) * size);
    if(points==NULL)
        return NULL;

    while (fgets(line, 80, fp)) {
        got = sscanf(line, "%lf%lf",
                     &points[npoints].time,
                     &points[npoints].value);

        if (got < 0) continue;
        if (got == 0) {
            printf("Line %ld has non-numeric data\n", npoints+1);
            break;
        }
        if (got == 1) {
            printf("Incomplete breakpoint found at %ld\n", npoints+1);
            break;
        }

        lasttime = points[npoints].time;
        if (++npoints == size) {
            brkpnt_t* tmp;
            size += npoints;
            tmp = (brkpnt_t*)realloc(points, sizeof(brkpnt_t) *size);
            if (tmp == NULL) {
                // NOTE: this state is very bad
                // and we should return NULL to caller.
                npoints = 0;
                free(points);
                points = NULL;
                break;
            }
            points = tmp;
        }
    }
    if (npoints)
        *psize = npoints;
    return points;
}

/* fp = fopen("envelope.brk", "r"); */
/* points = get_brkpnts(fp, &size); */
brkpnt_t maxpoint(const brkpnt_t* points, long npoints){
    int i;
    brkpnt_t point;

    point.time = points[0].time;
    point.value = points[0].value;

    for (i = 0; i < npoints; i++) {
        if (point.value < points[i].value) {
            point.value = points[i].value;
            point.time = points[i].time;
        }
    }
    return point;
}
