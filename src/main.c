#include <stdlib.h>
#include <stdio.h>
#include "brkpnt.h"

int main(int argc, char* argv[]) {
    long size;
    double dur;
    brkpnt_t point, *points;
    FILE* fp;

    printf("breakdur: find the duration of breakpoint file\n");

    if (argc < 2) {
        printf("usage: <bin_name> infile.txt \n");
        return 0;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        return 0;
    }

    size = 0;
    points = get_brkpnts(fp, &size);
    if (points == NULL) {
        printf("No breakpoints in the file\n");
        fclose(fp);
        return 1;
    }
    if (size < 2) {
        printf("Error: at least 2 breakpoints are required\n");
        free(points);
        fclose(fp);
        return 1;
    }

    // NOTE: breakpoints need to start at 0
    if (points[0].time != 0.0) {
        printf("Error: in datapoints: time must start @0.0\n");
        free(points);
        fclose(fp);
        return 1;
    }
    printf("read %.2ld breakpoints\n", size);

    dur = points[size - 1].time;
    printf("duration: %f seconds\n", dur);

    point = maxpoint(points, size);
    printf("max value: %f at %f seconds\n", point.value, point.time);
    free(points);
    fclose(fp);
    return 0;
}
