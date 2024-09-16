#ifdef INC_OSCB_H_

typedef struct oscb oscb_t;

oscb_t *new_oscil(unsigned long srate);

oscb_t *oscB(void);

double sinetick(oscb_t *p_osc, double freq);

#endif
