#ifndef INC_PANNING_H_

typedef struct panpos{
    double left;
    double right;
} panpos_t;

panpos_t simplepanning(double pos);

#endif
