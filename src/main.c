/*******************************************************************************
** envx.c :
*           extract amplitude envelope from mono soundfile
*******************************************************************************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <portsf.h>

#include "oscB.h"
#define DEBUG         -DDEBUG
#define TBLLEN        (1024)

#define DEFAULT_WINDOW_MSECS        (0xf)

enum { arg_progname, arg_samples, arg_srate, arg_amp, arg_freq,
        arg_nargs };

int main(int argc, char *argv[]) {
  int error = 0;

  if (argc < arg_nargs){

    argc -= 1;

    #ifdef DEBUG
    fprintf(stderr, "Error: Not enough arguments.\nYou gave %d instead of %d\n", argc, arg_nargs - 1);
    #endif
  }
  // NOTE:: make an oscilator bank......
  oscb_t **osc = NULL;
  double *osc_freqs = NULL, *osc_amps = NULL;
  unsigned long nosc;
  int nsamps = atoi(argv[arg_samples]);
  double outframe[nsamps];

  nosc = atoi(argv[arg_samples]);

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
    osc[i] = new_oscil(44100);
    if (osc[i] == NULL) {
      puts("No memory for oscillators\n");
      error++;
      goto exit;
    }
  }

  // NOTE::
  //        making a lookup table for a sine wave of 1024 length
  unsigned long i, len = TBLLEN;
  double step, table[TBLLEN];
  step = twopi / len;
  // NOTE::
  //        the array has one cycle because TBLLEN == twopi
  for (i = 0; i < TBLLEN; i++) {
    table[i] = sin(step * i);
    fprintf(stdout, "%lu\t%lf\n", i, table[i]);
  }

  // NOTE::
  //        truncting loop
  double curphase = 0.0;
  double tablen = (double) TBLLEN;
  double incr = step;
  for (i = 0; i < nsamps; i++) {
    int idx = (int) curphase; // phase truncated
    outframe[i] = (float) table[idx];
    curphase += incr;
    while (curphase >= tablen) {
      curphase -= tablen;
    }
    while (curphase < tablen) {
      curphase += tablen;
    }
    printf("Some signal: %lf\n", table[i]);
  }

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
}
