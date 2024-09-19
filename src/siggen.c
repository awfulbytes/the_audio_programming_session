#include <math.h>
#include "oscB.h"
#include "siggen.h"

/* #include "oscB.c" */

double sqtick(oscb_t *osc, double freq){

    double val;

    if(osc->curfreq != freq){
        osc->curfreq = freq;
        osc->incr = osc->twopiovrsr * freq;
    }

    if(osc->curphase <= M_PI){
        val = 1.0;
    }
    else{val = -1;}
    osc->curphase += osc->incr;

    if(osc->curphase >= twopi){
        osc->curphase -= twopi;
    }
    if(osc->curphase < 0){
        osc->curphase += twopi;
    }

    return val;
}

double sawdtick(oscb_t *osc, double freq){
    double val;

    if(osc->curfreq != freq){
        osc->curfreq = freq;
        osc->incr += osc->twopiovrsr * freq;
    }

    val = 1.0 - 2.0 * (osc->curphase * (1.0 / twopi));
    osc->curphase += osc->incr;

    if(osc->curphase >= twopi)
        osc->curphase -= twopi;
    if(osc->curphase < 0.0)
        osc->curphase += twopi;
    return val;
}

double sawutick(oscb_t *osc, double freq){
    double val;

    if (osc->curfreq != freq){
        osc->curfreq = freq;
        osc->incr = osc->twopiovrsr * freq;
    }

    val = (2.0 * (osc->curphase * (1.0 / twopi))) - 1.0;
    osc->curphase += osc->incr;

    if(osc->curphase >= twopi)
        osc->curphase -= twopi;
    if(osc->curphase < 0.0)
        osc->curphase += twopi;

    return val;
}

double tringtick(oscb_t *osc, double freq){
    double val;

    if (osc->curfreq != freq){
        osc->curfreq = freq;
        osc->incr = osc->twopiovrsr * freq;
    }

    val = (2.0 * (osc->curphase * (1.0 / twopi))) - 1.0;
    if (val < 0.0)
        val -= val;
    val = 2.0 * (val - 0.5);

    osc->curphase += osc->incr;
    if(osc->curphase >= twopi)
        osc->curphase -= twopi;
    if(osc->curphase < 0.0)
        osc->curphase += twopi;

    return val;
}
