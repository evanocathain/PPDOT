#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void print_usage(void);

int get_args(int argc, char** argv, char filename[], int* ascii, int* sigproc, int* nsamps, int* sp, float* spthresh, int* nsmax, int* fft, int* ffa, int* subzero, double* dm)
{
  if (argc==1){
    print_usage();
  }

  fprintf(stdout,"DESTROY - version 0.1\n\n"); /* Program launch ... */

  /* Initialise the default values */
  *ascii=0; 
  *sigproc=1;
  *sp=*fft=*ffa=0;
  *spthresh=4.00;
  *dm=0.0;
  *nsmax=10;

  /* Get values from header */
  /* ADD THIS LATER */

  /* Cycle through all the command line arguments */
  int i=1;
  while (i<argc){
    if (strings_equal(argv[i],"-o")){
      i++;
    }else if (strings_equal(argv[i],"-ascii")){
      *ascii=1;
      *sigproc=0;
    }else if (strings_equal(argv[i],"-sp")){
      *sp=1;
    }else if (strings_equal(argv[i],"-spthresh")){
      i++;
      *spthresh=atof(argv[i]);
    }else if (strings_equal(argv[i],"-dm")){
      i++;
      *dm=atof(argv[i]);
    }else if (strings_equal(argv[i],"-fft")){
      *fft=1;
    }else if (strings_equal(argv[i],"-ffa")){
      *ffa=1;
    }else if (strings_equal(argv[i],"-n")){
      i++;
      *nsamps=atoi(argv[i]);
    }else if (strings_equal(argv[i],"-nsmax")){
      i++;
      *nsmax=atoi(argv[i]);
    }else if (strings_equal(argv[i],"-h")){
      print_usage();
    }else if (strings_equal(argv[i],"--help")){
      print_usage();
    }
    i++;
  }
  strcpy(filename,argv[argc-1]);

  return(0);
}

void print_usage(void)
{
  fprintf(stdout,"\ndestroy - 'seeks' out periodic and/or transient signals in a noisey time series\n\n");
  fprintf(stdout,"usage: destroy -{options} {filename}\n\n");
  fprintf(stdout,"options:\n\n");
  fprintf(stdout,"-ascii        - set input file format to ascii (def=sigproc)\n");
  fprintf(stdout,"-dm           - give the dm (def=0.0 or from sigproc header)\n");
  fprintf(stdout,"-sp           - do a single pulse search\n");
  fprintf(stdout,"-fft          - do an FFT search [DOESN'T WORK YET!]\n");
  fprintf(stdout,"-ffa          - do an FFA search [DOESN'T WORK YET!]\n");
  fprintf(stdout,"Single Pulse Search Options\n");
  fprintf(stdout,"-spthresh val - set search threshold to val sigma (def=4.0)\n");
  fprintf(stdout,"-nsmax val    - set max number of smoothings to try (def=10)\n");
  fprintf(stdout,"-maura        - output additional file with highest S/N smoothings only (def=don't)[DOESN'T WORK YET!]\n");
  fprintf(stdout,"\n-h,--help     - prints this usage message\n");
  fprintf(stdout,"\n");

  exit(0);
}
