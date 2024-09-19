#ifdef M_PI
#ifndef M_PI
#define M_PI              (3.14159265358979323846)
#endif

#define twopi             (2 * M_PI)
#endif


typedef struct _oscb {
    double twopiovrsr; /*< Hold constant value. */
    double curfreq;
    double curphase;
    double incr;
} oscb_t;


typedef double (*tickfunc)(oscb_t *osc, double);

oscb_t* new_oscil(unsigned long srate);

oscb_t* oscB(void);

double sinetick(oscb_t *p_osc, double freq);
