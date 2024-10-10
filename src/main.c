/*******************************************************************************
 ** main.c :
 *          the entry point of all
 *******************************************************************************/
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* #include <portsf.h> */
#include <time.h>

#include "oscB.h"
#include "main.h"

#define SEMITN 2
#define DEBUG -DDEBUG
/* #define MUSIC -DMUSIC */
/* #define MEMORY__DEBUG               -DDEBUG */
#define TBLLEN (1024)
#define DEFSFR (44100)
#define DEFAULT_WINDOW_MSECS (0xf)

/* enum { arg_progname, arg_samples, arg_srate, arg_amp, arg_freq, */
/*         arg_nargs }; */

int main() {
  int error = 0;
  unsigned int nsamps;
  unsigned long nosc;

  /* if (argc < arg_nargs){ */

  /*   argc -= 1; */

  /*   #ifdef DEBUG */
  /*   fprintf(stderr, "Error: Not enough arguments.\nYou gave %d instead of
   * %d\n", argc, arg_nargs - 1); */
  /*   #endif */
  /* } */

  // NOTE:: make this fuzzable
  fprintf(stderr, "Give a number for samples: \n");
  scanf("%iu", &nsamps);

  // NOTE:: should scan for negatives also and handle those shit... thnx fuzzer
  if ((int)nsamps <= 0) {
    fprintf(stderr, "The number should be possitive i.e. > 0: %d\n", nsamps);
    return -1;
  } else if (nsamps > 20 * DEFSFR) {
    fprintf(
        stderr,
        "That is a big ass number the limit of the sample numbers posible to "
        "handle are %d\n",
        20 * DEFSFR);
    return -1;
  }

  // NOTE:: make this fuzzable
  /* fprintf(stderr, "Give a number for oscilators in the bank: \n"); */
  /* scanf("%ld", &nosc); */

  nosc = nsamps;

  // NOTE:: make an oscilator bank......
  oscb_t **osc = NULL;
  double *osc_freqs = NULL, *osc_amps = NULL;
  /* double outframe[nsamps]; */
  double dur = (double)nosc / (double)DEFSFR;
  fprintf(stderr, "duration in seconds: %lf\n", dur);
  double **sigbuf, **time = NULL;


  osc_amps = (double *)malloc(sizeof(double) * nosc);
  if (osc_amps == NULL) {
    puts("Memory for the amplitute array failed.\n");
    error++;
    goto exit;
  }

  osc_freqs = (double *)malloc(sizeof(double) * nosc);
  if (osc_freqs == NULL) {
    puts("Memory for the frequency array failed.\n");
    error++;
    goto exit;
  }

  osc = (oscb_t **)malloc(sizeof(oscb_t *) * nosc);
  if (osc == NULL) {
    puts("Memory for the oscilator bank array failed.\n");
    error++;
    goto exit;
  }

  sigbuf = (double **)malloc(sizeof(double *) * nosc);
  if (sigbuf == NULL) {
    puts("No sigbuf meeeeeem");
    error++;
    goto exit;
  }
  time = (double **)malloc(sizeof(double *) * nosc);
  if (time == NULL) {
    puts("No time meeeeeem");
    error++;
    goto exit;
  }

  fprintf(stderr, "Size of double: %zu bytes\n", sizeof(double));
  fprintf(stderr, "we fuck the first for");
  // NOTE::
  //        Initializing all the oscillators and corresponding time
  //        oscilation...???
  for (int i = 0; i < nosc; i++) {
    if (nosc > DEFSFR) {
      osc[i] = new_oscil(DEFSFR);
      time[i] = (double *)new_oscil(nosc);
      sigbuf[i] = (double *)new_oscil(nosc);
    } else {
      osc[i] = new_oscil(DEFSFR);
      time[i] = (double *)new_oscil(DEFSFR);
      sigbuf[i] = (double *)new_oscil(DEFSFR);
    }

    if (osc[i] == NULL) {
      puts("No memory for oscillators\n");
      error++;
      goto exit;
    }
    if (time[i] == NULL) {
      puts("No memory for time array buffer\n");
      error++;
      goto exit;
    }
    if (sigbuf[i] == NULL) {
      puts("No memory for signal array buffer\n");
      error++;
      goto exit;
    }

#ifdef MEMORY__DEBUG
    /* fprintf(stderr, "%d\t%lf\n", i, *osc[i]); */
    /* fprintf(stderr, "%pt\n", osc[i]); */
    fprintf(stderr, "%lu\n", sizeof(*osc[i]));
#endif
  }

  /* assert(*osc != NULL); */
  clock_t startt, endt;

  startt = clock();

  for (int i = 0; i < nosc; i++) {
    /* fprintf(stderr, "the time array scale: %lf\n", *time[i]); */
    *time[i] = (double)(i / ((double)(DEFSFR - 1)));
    // NOTE:: making the amplitute modulate exponentialy...
    //               this means that we need some of the variable to make a
    //               sweep but making it decay via the "-" sign or accending
    //               otherwize.
    //               ldexp(-i * 4e-5, 1)
    //               NOTE::
    //                      ramping up
    //                      ldexp(-i * 4e-5, -1)
    /* osc_amps[i] = 0.8 * exp(-i * 0.000008 * 0.2); */
    // 6.66 * exp(i * 0.00003 * exp(-0.0002))
    /* osc_freqs[i] = (double) 440 / (double) SEMITN * pow(i, 0.02); */
    osc_freqs[i] = 20.0;
    osc_amps[i] = dbelling(1.3);
  }
  /* fprintf(stderr, "the time array scale: %lf\n", *time[nosc]); */
  tickfunc ticker = sqtick;

  for (int i = 0; i < nosc; i++) {
    /* if (i < nosc/2) */
    /* if (i % 2) */
    /*   *sigbuf[i] = osc_amps[i] * sinetick(*osc, osc_freqs[i]); */
    /* if (i % 16) */
    /*   *sigbuf[i] = osc_amps[i] * sinetick(*osc, osc_freqs[i]); */
    /* if (i > nosc - 4400) */
    /*   *sigbuf[i] = -osc_amps[i] * sinetick(*osc, 100); */
    /* else */
    *sigbuf[i] = osc_amps[i] * (ticker(*osc, osc_freqs[i]));

#ifndef MUSIC
    /* fprintf(stdout, "%f\t%lf\n", osc_freqs[i], *sigbuf[i]); */
    fprintf(stdout, "%f\t%lf\n", *time[i], *sigbuf[i]);
#endif
#ifdef MUSIC
    fprintf(stdout, "%lf\n", *sigbuf[i]);
#endif
  }
  goto exit;

  // NOTE::
  //        making a lookup table for a sine wave of 1024 length
  /* unsigned long i, len = TBLLEN; */
  /* double step, table[TBLLEN]; */
  /* step = twopi / len; */
  /* // NOTE:: */
  /* //        the array has one cycle because TBLLEN == twopi */
  /* for (i = 0; i < TBLLEN; i++) { */
  /*   table[i] = sin(step * i); */
  /* } */
  /* /\* fprintf(stdout, "%d\t%lf\n", TBLLEN, table[TBLLEN-1]); *\/ */

  /* // NOTE:: */
  /* //        truncting loop */
  /* double curphase = 0.0; */
  /* double tablen = (double) TBLLEN; */
  /* double incr = step; */
  /* for (i = 0; i < tablen; i++) { */
  /*   int idx = (int) curphase; // phase truncated */
  /*   outframe[i] = (float) table[idx]; */
  /*   curphase += incr; */
  /*   while (curphase >= tablen) { */
  /*     curphase -= tablen; */
  /*   } */
  /*   while (curphase < tablen) { */
  /*     curphase += tablen; */
  /*   } */
  /*   printf("%lu\t%lf\n", i, table[i]); */
  /* } */

exit:
  if (osc_amps)
    free(osc_amps);
  if (osc_freqs)
    free(osc_freqs);
  // NOTE:: free your own malloc brother
  while (nosc > 0) {
    nosc -= 1;
    free(osc[nosc]);
    free(sigbuf[nosc]);
    free(time[nosc]);
  }
  if (*osc)
    free(osc);
  if (*sigbuf || *time) {
    free(sigbuf);
    free(time);
  }
  endt = clock();
  double elapsed = (endt - startt) / (double)CLOCKS_PER_SEC;
  fprintf(stderr, "Time to procces was: %f [ms]\n", elapsed);
}
