/*******************************************************************************
** envx.c :
*           extract amplitude envelope from mono soundfile
*******************************************************************************/
#include <portsf.h>
#include <stdio.h>
#include <stdlib.h>

#include "maxsamp.h"

#define DEFAULT_WINDOW_MSECS        (0xf)

enum { ARG_PROGNAME, ARG_INFILE, ARG_OUTFILE, ARG_NARGS };

int main_for_envx2brkpt(int argc, char *argv[]) {
  if (psf_init()){
    printf("no portsf for you babe\n");
    return 1;
  }

  if (argc < ARG_NARGS) {
    printf("insufficient arguments.\n"
           "usage: <bin_name> infile outfile.brk\n");
    return 1;
  }

  double windur = DEFAULT_WINDOW_MSECS;
  unsigned long winsize, npoints;

  PSF_PROPS inprops;
  long framesread;
  /* init all resource vars to default states */
  int ifd = -1, ofd = -1;
  int error = 0;
  /* psf_format outformat = PSF_FMT_UNKNOWN; */
  /* PSF_CHPEAK *peaks = NULL; */
  float *frame = NULL;


  printf("ENVX: extract amplitute envelope from mono soundfile.\n");
  /* ifd = psf_sndOpen(argv[ARG_INFILE], &props, 0); */

  /* create the break point file */
  FILE *fp = fopen(argv[ARG_OUTFILE], "w");
  if (fp == NULL) {
    printf("cannot create breakpoint file %s.\n", argv[ARG_OUTFILE]);
    error++;
    goto exit;
  }
  /* allocate space for one sample frame */
  frame = (float *)malloc(inprops.chans * sizeof(float));
  if (frame == NULL) {
    puts("No memory!\n");
    error++;
    goto exit;
  }

  ifd = psf_sndOpen(argv[ARG_INFILE], &inprops, 0);
  if (ifd < 0) {
    printf("Unable to open the infile %s\n", argv[ARG_INFILE]);
    return 1;
  }
  if (inprops.chans > 1){
    printf("file should contain 1 channel but found %d channels in the input file\n",
           inprops.chans);
    return 1;
  }

  // NOTE:: Here we implement a check for the flag (right / not or none)
  if (argc > 1) {
    char flag;
    while (argv[1][0] == '-') {
      flag = argv[1][1];
      switch (flag) {

      case '\0':
        printf("Error: missing flag name\n");
        return 1;

      case 'w':
        windur = atof(&argv[1][2]);
        if (windur <= 0.0) {
          printf("A duration must be possitive at all times to have physical "
                 "meaning of a window\n");
          return 1;
        }
        break;

      default:
        break;
      }
      argc--;
      argv++;
    }
  }

  // NOTE:: in C /= means devide and assin to variable name
  windur /= 1000.0;
  winsize = (unsigned long)(windur * inprops.srate);

  float *inframe = (float *)malloc(winsize * sizeof(float));
  if (inframe == NULL) {
    puts("No memory for the inframe allocation\n");
    error++;
    goto exit;
  }

  double brktime = 0.0;
  while ((framesread = psf_sndReadFloatFrames(ifd, inframe, winsize)) > 0) {
    double amp;
    amp = maxsamp(inframe, framesread);

    if (fprintf(fp, "%f\t%f\n", brktime, amp) < 2) {
      printf("Failed to write to the breakpoint file %s\n", argv[ARG_OUTFILE]);
      error++;
      break;
    }

    npoints++;
    brktime += windur;
  }

  /* /\* and allocate space for PEAK info *\/ */
  /* peaks = (PSF_CHPEAK *)malloc(props.chans * sizeof(PSF_CHPEAK)); */
  /* if (peaks == NULL) { */
  /*   puts("No memory!\n"); */
  /*   error++; */
  /*   goto exit; */
  /* } */
  /* printf("copying....\n"); */
  /* /\* single-frame loop to do copy, report any errors *\/ */
  /* framesread = psf_sndReadFloatFrames(ifd, frame, 1); */
  /* totalread = 0; /\* running count of sample frames *\/ */
  /* while (framesread == 1) { */
  /*   totalread++; */
  /*   if (psf_sndWriteFloatFrames(ofd, frame, 1) != 1) { */
  /*     printf("Error writing to outfile\n"); */
  /*     error++; */
  /*     break; */
  /*   } */
  /*   /\* <---- do any processing here! ------> *\/ */
  /*   framesread = psf_sndReadFloatFrames(ifd, frame, 1); */
  /* } */
  if (framesread < 0) {
    printf("Error reading infile. Outfile is incomplete.\n");
    error++;
  } else
    printf("Done. %d errors\n", error);
  printf("%lu total breakpoints to %s\n", npoints, argv[ARG_OUTFILE]);

/* do all cleanup */
exit:
  if (ifd >= 0)
    psf_sndClose(ifd);
  if (ofd >= 0)
    psf_sndClose(ofd);
  if (fp)
    if (fclose(fp))
      printf("envx: failed to close the output file %s\n", argv[ARG_OUTFILE]);
  if (inframe)
    free(inframe);
  /* if (peaks) */
  /*   free(peaks); */
  psf_finish();
  return error;
}
