#include "panning.h"

panpos_t simplepanning(double pos){
    panpos_t position;
    pos *= 0.5;
    position.left = pos - 0.5;
    position.right = pos + 0.5;

    return position;
}
