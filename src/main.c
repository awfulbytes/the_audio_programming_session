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
#include "siggen.h"

#define DEBUG -DDEBUG
/* #define MUSIC -DMUSIC */
/* #define MEMORY__DEBUG               -DDEBUG */
#define TBLLEN (1024)
#define DEFSFR (44100)
#define DEFAULT_WINDOW_MSECS (0xf)

/* enum { arg_progname, arg_samples, arg_srate, arg_amp, arg_freq, */
/*         arg_nargs }; */

int main(int argc, char *argv[]) {
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
  } else if (nsamps > INT_MAX) {
    fprintf(stderr,
            "That is a big ass number the limit of the numbers posible to "
            "handle are %d\n",
            INT_MAX);
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

  // TODO:: make the signal to be printed in seconds instead of the idx array.
  //        here im able to determine the ammount of seconds a signal has
  //        because i have the sampling frequency and the number of samples the
  //        user gave... this is bad idea i have to determine the exact amount
  //        of samples via the Niquist theorem of sf and aliasing... I see a lot
  //        now...
  /* if (nosc > DEFSFR) { */
  /*   fprintf(stderr, "nosc before: %lu\n", nosc); */
  /*   nosc = (double) (nosc + (nosc - (double) DEFSFR)); */
  /*   fprintf(stderr, "size of new stuff: %lu\n", sizeof(*sigbuf)); */
  /* } */

  for (int i = 0; i < nosc; i++) {
    /* fprintf(stderr, "the time array scale: %lf\n", *time[i]); */
    *time[i] = (double)(i / ((double)(DEFSFR - 1)));
    // NOTE:: making the amplitute modulate exponentialy...
    //               this means that we need some of the variable to make a
    //               sweep but making it decay via the "-" sign or accending
    //               otherwize.
    osc_amps[i] = exp(i * 0.00003 * 0.2);
  }
  /* fprintf(stderr, "the time array scale: %lf\n", *time[nosc]); */

  for (int i = 0; i < nosc; i++) {
    /* if (i < nosc/2) */
    if (i % 2)
      *sigbuf[i] = osc_amps[i] * sinetick(*osc, 100);
    if (i % 16)
      *sigbuf[i] = osc_amps[i] * sinetick(*osc, 40);
    else
      *sigbuf[i] = osc_amps[i] * sinetick(*osc, 50);

#ifndef MUSIC
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
