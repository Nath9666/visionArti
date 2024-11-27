/* Timer Linux : horloge gettimeofday() */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


#define NB 100000

void deroutementSignal(int arg);
int n = 0;
struct timeval tv[2];

int main(int argc, char * argv[])
{
  struct itimerval timer;
  int freq, nusec;
  double T;
  // Mesure
  double dDeb, dFin, dTemps;


  if (argc != 2)
  {
    fprintf(stderr,"USAGE : ./TestFreqTimerUnix freq (> 1) \n");
    exit (0);
  }
  freq = atoi(*++argv);
  // Installer la fonction de deroutement du signal SIGALRM
  if (signal(SIGALRM, deroutementSignal) == SIG_ERR)
  {
    fprintf(stderr,"Erreur d'installation de la fonction de deroutement \n");
    exit(0);
  }
  

  // Preparer la structure itimerval
  timer.it_value.tv_sec = 3;
  timer.it_value.tv_usec = 500000;

  /* Calcul de la Periode */
  T = 1.0 / freq;
  nusec = (int) (1000000 * T);
  fprintf(stderr,"Freq = %d, Periode = %lf, susec = %d\n", 
    freq, T, nusec);

  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = nusec; 

  
  fprintf(stderr,"Premier : 3,5 s, ensuite toute les secondes \n");
  // Programmer le timer
  setitimer(ITIMER_REAL, & timer, NULL);
  fprintf(stderr,"Depart \n");
  system("date +\"%H:%M:%S:%N\"");
  while (1)
  {
    pause();
    if (n > NB)
    break;
  }
  gettimeofday(& (tv[1]), NULL); // stop

  /* --- Calcul de la frequence obtenue --- */
  dDeb = (double)(tv[0].tv_usec) * 0.000001 + (double)tv[0].tv_sec;
  dFin = (double)(tv[1].tv_usec) * 0.000001 + (double)tv[1].tv_sec;
  dTemps = (dFin - dDeb);
  printf("Periode en usec : %lf \n", 1000000.0 * dTemps / NB);
  T = dTemps / NB;
  freq = (int)(1.0 / T);

  printf("Frequence obtenue : %d\n",freq);

  return EXIT_SUCCESS;
}void deroutementSignal(int arg)
{
  n++;
  if (n == 1) // start
     gettimeofday(& (tv[0]), NULL);
  
}