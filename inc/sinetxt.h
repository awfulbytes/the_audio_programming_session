#ifndef INC_SINETXT_H_

#ifndef M_PI
#define M_PI (3.141592654)
#endif

enum {ARG_NAME, ARG_NSAMPS, ARG_FREQ, ARG_SR, ARG_NARGS};

void sintxt(int nsamps, double freq, double srate);

#endif
