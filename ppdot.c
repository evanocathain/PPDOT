#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int strings_equal (char *string1, char *string2);
void print_usage(void);
int get_args(int argc, char** argv, int* psr, int* magnetar, int* xdins, int* binary, int* rrat, int* nuller, int* fermi, int* glitch, int* E, int* B, int* T, int* BQC, int* death, int* top, int* bottom, int* request, char* psr_name);

int main ( int argc, char* argv[])
{
  //  FILE *gnuplot = popen("/usr/bin/gnuplot -persist","w");
  FILE *gnuplot = popen("/usr/local/bin/gnuplot -persist","w");
  char path[]="./lists/";
  int check=0;
  int psr,magnetar,xdins,binary,rrat,nuller,fermi,glitch,E,B,T,BQC,death;
  int top,bottom,request;
  char psr_name[10];

  check=get_args(argc,argv,&psr,&magnetar,&xdins,&binary,&rrat,&nuller,&fermi,&glitch,&E,&B,&T,&BQC,&death,&top,&bottom,&request,psr_name);
  if (check !=0) return(1);

  //  fprintf(gnuplot,"set term x11\n");
  fprintf(gnuplot,"set title \"P-Pdot Diagram\"\n");
  fprintf(gnuplot,"set xlabel \"log(P/second)\"\n");
  fprintf(gnuplot,"set ylabel \"log(Pdot)\"\n");

  //  fprintf(gnuplot,"set key 8.0e-3,1.0e-11 Right box -1\n");
  fprintf(gnuplot,"set key top left\n");
  fprintf(gnuplot,"set key spacing 1.2\n");
  fprintf(gnuplot,"set key box\n");

  fprintf(gnuplot,"set logscale xy\n");
  if (top==1 && bottom==0){
    fprintf(gnuplot,"set yrange [1e-15:1e-9]\n");
  }else if (top==0 && bottom==1){
    fprintf(gnuplot,"set yrange [1e-22:1e-15]\n");
  }else{
    fprintf(gnuplot,"set yrange [1e-22:1e-9]\n");
  }
  fprintf(gnuplot,"set xrange [0.001:40]\n");
  if (death==1 || BQC==1){ 
    /* Chen & Ruderman 1993 (cr93a) death line */
    fprintf(gnuplot,"death1(x)=10**(-14.36)*(x**(2.75))\n"); // high-B
    fprintf(gnuplot,"death2(x)=10**(-16.16)*(x**(2.25))\n"); // low-B
    /* Baring & Harding 1998 (bh98) photon splitting line */
    fprintf(gnuplot,"BQC1(x)=(7.9e-13)*(x**(-0.733))\n"); 
    if (death==1 && BQC==0){
      fprintf(gnuplot,"plot death2(x) w filledcurves x1 lt 9 notitle\n");
    }
    else if (death==0 && BQC==1){
      //      fprintf(gnuplot,"plot BQC1(x) w filledcurves x2 lt 4 notitle\n");
      fprintf(gnuplot,"plot BQC1(x) w li lt 8 notitle\n");
    }
    else{
      //      fprintf(gnuplot,"plot death2(x) w filledcurves x1 lt 9 notitle\n");
      fprintf(gnuplot,"plot death2(x) w li lt -1 lw 2 notitle\n");
      //      fprintf(gnuplot,"replot BQC1(x) w filledcurves x2 lt 4 notitle\n");
      fprintf(gnuplot,"replot BQC1(x) w li lt 0 notitle\n");
    }
    fprintf(gnuplot,"replot \"%sall_psrcat\" using 1:2 wi points pt 7 ps 0.5 lt 2 title \"Radio PSRs\"\n",path);
  }
  else if (death==0 && BQC==0){
    fprintf(gnuplot,"plot \"%sall_psrcat\" using 1:2 pt 5 lt 0 title \"Radio PSRs\"\n",path);
  }
  if (E==1){
    fprintf(gnuplot,"set label \"10^{27} erg/s\" rotate by 40 front at 0.6,1.0e-21\n");
    fprintf(gnuplot,"set label \"10^{30} erg/s\" rotate by 40 front at 0.1,6.0e-21\n");
    fprintf(gnuplot,"set label \"10^{33} erg/s\" rotate by 40 front at 7.0e-02,3.0e-18\n");
    fprintf(gnuplot,"set label \"10^{36} erg/s\" rotate by 40 front at 2.0e-02,5.0e-17\n");
    fprintf(gnuplot,"set label \"10^{39} erg/s\" rotate by 40 front at 5.0e-03,8.0e-16\n");

    fprintf(gnuplot,"E27(x)=2.536e-20*(x**3)\n");
    fprintf(gnuplot,"E30(x)=2.536e-17*(x**3)\n");
    fprintf(gnuplot,"E33(x)=2.536e-14*(x**3)\n");
    fprintf(gnuplot,"E36(x)=2.536e-11*(x**3)\n");
    fprintf(gnuplot,"E39(x)=2.536e-8*(x**3)\n");
    fprintf(gnuplot,"replot E27(x) lt 0 lw 5 notitle,E30(x) lt 0 lw 5 notitle,E33(x) lt 0 lw 5 notitle,E36(x) lt 0 lw 5 notitle,E39(x) lt 0 lw 5 notitle\n");
  }
  if (B==1){
    fprintf(gnuplot,"set label \"10^{8} G\" rotate by -15 front at 8.0e-03,5.0e-22\n");
    fprintf(gnuplot,"set label \"10^{10} G\" rotate by -15 front at 5.0e-03,8.0e-18\n");
    fprintf(gnuplot,"set label \"10^{12} G\" rotate by -15 front at 5.0e-03,7.0e-14\n");
    fprintf(gnuplot,"set label \"10^{14} G\" rotate by -15 front at 2.0e-02,2.0e-10\n");
    fprintf(gnuplot,"B8(x)=9.76e-24/x\n");
    fprintf(gnuplot,"B10(x)=9.76e-20/x\n");
    fprintf(gnuplot,"B12(x)=9.76e-16/x\n");
    fprintf(gnuplot,"B14(x)=9.76e-12/x\n");
    fprintf(gnuplot,"B16(x)=9.76e-8/x\n");
    fprintf(gnuplot,"replot B8(x) lt -1 notitle,B10(x) lt -1 notitle,B12(x) lt -1 notitle,B14(x) lt -1 notitle,B16(x) lt -1 notitle\n");
  }
  if (T==1){
    fprintf(gnuplot,"set label \"1 kyr\" rotate by 15 front at 1.2e-03,3.0e-14\n");
    fprintf(gnuplot,"set label \"100 kyr\" rotate by 15 front at 1.2e-03,3.0e-16\n");
    fprintf(gnuplot,"set label \"10 Myr\" rotate by 15 front at 1.2e-03,3.0e-18\n");
    fprintf(gnuplot,"set label \"1 Gyr\" rotate by 15 front at 1.2e-03,3.0e-20\n");
    fprintf(gnuplot,"T3(x)=1.59e-11*x\n");
    fprintf(gnuplot,"T5(x)=1.59e-13*x\n");
    fprintf(gnuplot,"T7(x)=1.59e-15*x\n");
    fprintf(gnuplot,"T9(x)=1.59e-17*x\n");
    fprintf(gnuplot,"replot T3(x) lt 0 lw 3 notitle,T5(x) lt 0 lw 3 notitle,T7(x) lt 0 lw 3 notitle,T9(x) lt 0 lw 3 notitle\n");
  }
  fprintf(gnuplot,"replot \"%sall_psrcat\" using 1:2 wi points pt 7 ps 0.5 lt 2 notitle\n",path);
  if (magnetar==1){
    fprintf(gnuplot,"replot \"%smagnetars_confirmed\" using 3:4 pt 11 lt 1 ps 2 title \"Magnetars\"\n",path);
  }
  if (xdins==1){
    fprintf(gnuplot,"replot \"%sxdins_confirmed\" pt 5 ps 1.5 lt 3 lw 2 title \"XINS\"\n",path);
  }
  if (rrat==1){
    fprintf(gnuplot,"replot \"%srrats\" pt 7 ps 1 lt -1 title \"RRATs\"\n",path);
    fprintf(gnuplot,"replot \"%smy_rrats\" every ::1 pt 7 ps 1 lt -1 notitle\n",path); 
    //    fprintf(gnuplot,"replot \"%srrats_unpublished\" pt 7 ps 1 lt -1 notitle\n",path); 
  }
  if (binary==1){
    fprintf(gnuplot,"replot \"%sbinaries\" pt 4 ps 2 lt 2 title \"Binaries\"\n",path);
  }
  if (glitch==1){
    fprintf(gnuplot,"replot \"%sglitch_test\" using 2:3 pt 15 ps 2 lt 7 title \"Glitch Observed\"\n",path);
  }
  if (request==1){
    fprintf(gnuplot,"replot \"requested_psr\" using 1:2 pt 6 ps 2 lt 3 title \"%s\"\n",psr_name);
  }
  if (fermi==1){
    fprintf(gnuplot,"replot \"%sfermi_psrs\" using 2:3 pt 6 ps 2 lt 4 title \"Fermi PSRs\"\n",path);
  }

  fprintf(gnuplot,"set terminal postscript enhanced color solid\n");
  fprintf(gnuplot,"set output \"ppdot.ps\"\n");
  //  fprintf(gnuplot,"set terminal png color\n");
  //  fprintf(gnuplot,"set output \"ppdot.png\"\n");
  //fprintf(gnuplot,"set terminal pdf color\n");
  //fprintf(gnuplot,"set output \"ppdot.pdf\"\n");
  fprintf(gnuplot,"replot\n");

  fprintf(gnuplot,"exit \n");
  pclose(gnuplot);
  

  return(0);
}

/* FUNCTION DEFINITIONS */
int strings_equal (char *string1, char *string2)
{
  if (!strcmp(string1,string2)) {
    return 1;
  } else {
    return 0;
  }
}

int get_args(int argc, char** argv, int* psr, int* magnetar, int* xdins, int* binary, int* rrat, int* nuller, int* fermi, int* glitch, int* E, int* B, int* T, int* BQC, int* death, int* top, int* bottom, int* request, char* psr_name)
{
  int ret,compipe[2];

  /* Set default values */
  *psr=1;
  *magnetar=0;
  *xdins=0;
  *binary=0;
  *rrat=0;
  *nuller=0;
  *fermi=0;
  *glitch=0;
  *E=0;
  *B=0;
  *T=0;
  *BQC=0;
  *death=0;
  *top=-1;
  *bottom=-1;
  *request=0;

/* Cycle through all the command line arguments */
  int i=1;
  while (i<argc){
    if (strings_equal(argv[i],"-m")){
      *magnetar=1;
    }else if (strings_equal(argv[i],"-h")){
      print_usage();
    }else if (strings_equal(argv[i],"--help")){
      print_usage();
    }else if (strings_equal(argv[i],"-all")){
      *xdins=*binary=*rrat=*magnetar=*nuller=1;
      *glitch=*fermi=1;  // fermi, SNR associations ...
      *E=*B=*T=*BQC=1; // death, BQC ...
    }else if (strings_equal(argv[i],"-x")){
      *xdins=1;
    }else if (strings_equal(argv[i],"-b")){
      *binary=1;
    }else if (strings_equal(argv[i],"-r")){
      *rrat=1;
    }else if (strings_equal(argv[i],"-n")){
      *nuller=1;
    }else if (strings_equal(argv[i],"-g")){
      *glitch=1;
    }else if (strings_equal(argv[i],"-fermi")){
      *fermi=1;
    }else if (strings_equal(argv[i],"-E")){
      *E=1;
    }else if (strings_equal(argv[i],"-B")){
      *B=1;
    }else if (strings_equal(argv[i],"-T")){
      *T=1;
    }else if (strings_equal(argv[i],"-BQC")){
      *BQC=1;
    }else if (strings_equal(argv[i],"-death")){
      *death=1;
    }else if (strings_equal(argv[i],"-top")){
      *top=1;
      *bottom=0;
    }else if (strings_equal(argv[i],"-bottom")){
      *bottom=1;
      *top=0;
    }else if (strings_equal(argv[i],"-psr")){
      i++;
      *request=1;
      strcpy(psr_name,argv[i]);
      pipe(compipe);
      if(!fork()){
	freopen("requested_psr","w",stdout);
	ret=execl("/bin/grep","grep",argv[i], "lists/psrcat",NULL);
	freopen("CON","w",stdout);
      }
    }
    i++;
  }

  return(0);

}

void print_usage(void)
{
  fprintf(stdout,"\nppdot - plots a period - period derivative diagram highlighting \nwhatever you specify \n\n");
  fprintf(stdout,"usage: ppdot -{options}\n\n");
  fprintf(stdout,"options:\n\n");
  fprintf(stdout,"-all          - highlight everything\n");
  fprintf(stdout,"-b            - binaries\n");
  fprintf(stdout,"-g            - glitches\n");
  fprintf(stdout,"-m            - magnetars\n");
  fprintf(stdout,"-n            - nullers\n");
  fprintf(stdout,"-r            - rrats\n");
  fprintf(stdout,"-x            - xdins\n");
  fprintf(stdout,"-bottom       - plot the bottom half only\n");
  fprintf(stdout,"-top          - plot the top half only\n");
  fprintf(stdout,"-E            - constant Edot lines\n");
  fprintf(stdout,"-B            - constant B lines\n");
  fprintf(stdout,"-T            - constant characteristic age lines\n");
  fprintf(stdout,"-BQC          - quantum critical B line\n");
  fprintf(stdout,"-death        - death line\n");
  fprintf(stdout,"-psr {name}   - highlights pulsar {name} on plot\n");
  fprintf(stdout,"\n-h,--help     - prints this usage message\n");
  fprintf(stdout,"\n");

  exit(0);
}
