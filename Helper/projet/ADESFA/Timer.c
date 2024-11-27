#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void gestionnaire (int sig);
int nDecl = 0;

int main (int argc, char **argv)
{
  fprintf(stderr, "Pid = %d, Ppid = %d\n", getpid(), getppid());

  if (signal (SIGALRM, gestionnaire) == SIG_ERR)
  {
    fprintf(stderr,"Erreur d'association SIGALRM\n");
    exit(0);
  }

  alarm(5);
  fprintf(stderr,"Entree dans la boucle Premier declanchement \n");
  system("date +\"%H:%M:%S:%N\"");
  while (1)
  {
    pause(); // attente passive  
  }
  
  system("date +\"%H:%M:%S:%N\"");
  return EXIT_SUCCESS;
}


void gestionnaire (int sig)
{
  nDecl++;
  if (sig == SIGALRM)
    fprintf(stderr,"Signal SIGALRM : reçu : %d fois\n",nDecl);
  else
    fprintf(stderr,"Signal Autre : reçu \n");

  system("date +\"%H:%M:%S:%N\"");
  alarm(2);
  return;
}

