/* Timer Linux : horloge gettimeofday() */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


void deroutementSignal(int arg);
int n = 0;

int main(int argc, char * argv[])
{
  struct itimerval timer;
  // Installer la fonction de deroutement du signal SIGALRM
  if (signal(SIGALRM, deroutementSignal) == SIG_ERR)
  {
    fprintf(stderr,"Erreur d'installation de la fonction de deroutement \n");
    exit(0);
  }
  
  // Preparer la structure itimerval
  timer.it_value.tv_sec = 3;
  timer.it_value.tv_usec = 500000;
  
  timer.it_interval.tv_sec = 1;
  timer.it_interval.tv_usec = 0;
  
  fprintf(stderr,"Premier : 3,5 s, ensuite toute les secondes \n");
  // Programmer le timer
  setitimer(ITIMER_REAL, & timer, NULL);
  fprintf(stderr,"Depart \n");
  system("date +\"%H:%M:%S:%N\"");
  while (1)
  {
    pause();
  }
  return EXIT_SUCCESS;
}void deroutementSignal(int arg)
{
  n++;
  fprintf(stderr, "Interruption %d : \n", n);
  system("date +\"%H:%M:%S:%N\"");
}