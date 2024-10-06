/*******************************************************************************
 ** main.c :
*          the entry point of all
*******************************************************************************/
#include <limits.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <portsf.h>
#include <time.h>

#include "siggen.h"
#include "oscB.h"
#define DEBUG         -DDEBUG
/* #define MEMORY__DEBUG -DDEBUG */
#define TBLLEN        (1024)
#define DEFSFR        (44100)

#define DEFAULT_WINDOW_MSECS        (0xf)

/* enum { arg_progname, arg_samples, arg_srate, arg_amp, arg_freq, */
/*         arg_nargs }; */

int main(int argc, char *argv[]) {
  int error = 0;
  unsigned int nsamps;
  unsigned long nosc;

  /* if (argc < arg_nargs){ */

  /*   argc -= 1; */

  /*   #ifdef DEBUG */
  /*   fprintf(stderr, "Error: Not enough arguments.\nYou gave %d instead of %d\n", argc, arg_nargs - 1); */
  /*   #endif */
  /* } */

  // NOTE:: make this fuzzable
  fprintf(stderr, "Give a number for samples: \n");
  scanf("%iu", &nsamps);

  // NOTE:: should scan for negatives also and handle those shit... thnx fuzzer
  if ((int) nsamps <= 0) {
    fprintf(stderr, "The number should be possitive: %d\n", nsamps);
    return -1;
  } else if (nsamps > INT_MAX) {
    fprintf(stderr, "That is a big ass number the limit of the numbers posible to handle are %d\n",
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

  osc_amps = (double *) malloc(sizeof(double) * nosc);
  if (osc_amps == NULL) {
    puts("Memory for the amplitute array failed.\n");
    error++;
    goto exit;
  }

  osc_freqs = (double *) malloc(sizeof(double) * nosc);
  if (osc_freqs == NULL) {
    puts("Memory for the frequency array failed.\n");
    error++;
    goto exit;
  }

  osc = (oscb_t **) malloc(sizeof(oscb_t *) * nosc);
  if (osc == NULL) {
    puts("Memory for the oscilator bank array failed.\n");
    error++;
    goto exit;
  }

  // NOTE::
  //        Initializing all the oscillators
  for (int i = 0; i < nosc; i++) {
    osc[i] = new_oscil(DEFSFR);
    if (osc[i] == NULL) {
      puts("No memory for oscillators\n");
      error++;
      goto exit;
    }
    #ifdef MEMORY__DEBUG
    /* fprintf(stderr, "%d\t%lf\n", i, *osc[i]); */
    fprintf(stderr, "%pt\n", osc[i]);
    /* assert(*osc[i]-> == 0.0); */
    #endif
  }

  clock_t startt, endt;

  startt = clock();

  // TODO:: make the signal to be printed in seconds instead of the idx array.
  //        here im able to determine the ammount of seconds a signal has
  //        because i have the sampling frequency and the number of samples the
  //        user gave... this is bad idea i have to determine the exact amount
  //        of samples via the Niquist theorem of sf and aliasing... I see a lot
  //        now...
  double dur = (double) nosc / (double) DEFSFR;
  fprintf(stderr, "duration in seconds: %lf\n", dur);
  double sigbuf[DEFSFR];
  for (int i = 0; i < nosc; i++){
    /* double some =  sinetick(osc[i], 200.0); */
    sigbuf[i] = sinetick(*osc, 200);
    fprintf(stdout, "%d\t%lf\n", i, sigbuf[i]);
  }

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
  while (nsamps > 0) {
    nsamps -= 1;
    free(osc[nsamps]);
  }
  if (*osc)
    free(osc);

  endt = clock();
  double elapsed = (endt - startt) / (double) CLOCKS_PER_SEC;
  fprintf(stderr, "Time to procces was: %f [ms]\n", elapsed);
}
