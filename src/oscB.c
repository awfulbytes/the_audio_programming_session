#include <stdlib.h>
#include <math.h>

#include "oscB.h"


oscb_t* new_oscil(unsigned long srate){
    oscb_t *p_osc;
    p_osc = (oscb_t *) malloc(sizeof(*p_osc));

    if (p_osc == ((void *)0))
      return NULL;

    p_osc -> twopiovrsr      = twopi / (double) srate;
    p_osc -> curfreq         = 0.0;
    p_osc -> curphase        = 0.0;
    p_osc -> incr            = 0.0;

    return p_osc;

}

/** Free after usage!!
 * This function allocates memory for the oscillator so the user is responsible
 * **to clear** the memory on the heap.
 */
oscb_t* oscB(void){
    oscb_t *osc = (oscb_t *) malloc(sizeof(oscb_t));

    if (osc == ((void *)0))
        return NULL;
    return osc;
}

double sinetick(oscb_t *p_osc, double freq){
    double val;

    val = sin(p_osc->curphase);
    if (p_osc->curfreq != freq){
        p_osc->curfreq = freq;
        p_osc->incr = p_osc->twopiovrsr * freq;
    }
    p_osc->curphase += p_osc->incr;
    if (p_osc->curphase >= twopi)
        p_osc->curphase -= twopi;
    if (p_osc->curphase < 0.0)
        p_osc->curphase += twopi;
    return val;
}

/* double oscB(double freq){ */
/*     double startphase, srate, curphase, incr; */
/*     startphase = 0.0; */
/*     srate = 44100.0; */
/*     curphase = 0.0; */
/*     incr = freq * twopi / srate; */

/*     for (int i=0; i < outsamps; i++){ */
/*         output[i] = (float) sin(curphase); */
/*         curphase += incr; */
/*         if (curphase >= twopi){ */
/*             curphase -= twopi; */
/*         } */
/*     } */
/* } */
