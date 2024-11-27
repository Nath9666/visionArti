#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <string.h>

struct ParamIn
{
  int num;
  double dble;
};
typedef struct ParamIn PARAMIN;

typedef struct 
{
  long long ll;
  char nom[100];
} PARAMOUT ;


void *fonction_thread (void *);
int main (int argc, char **argv)
{
  int ret;
  pthread_t thread;
  PARAMIN ParIn;
  void *AddRet;
  PARAMOUT ParOut;

  ParIn.num = 1;
  ParIn.dble = 3.14;
  fprintf(stderr, "Processus : Pid = %d, Ppid = %d\n", getpid(), getppid());

  /* --- Creation du Thread --- */
  if ((ret = pthread_create (&thread, NULL, fonction_thread, (void*)(&ParIn))) 
    !=  0)
  {
    fprintf(stderr,"Erreur creation \n");
    exit(0);
  }
  fprintf(stderr,"Thread cree : %ld\n",thread);
  sleep(2);
  fprintf(stderr,"Fin activite du Processus \n");
  system("date +\"%H:%M:%S:%N\"");
  
  pthread_join(thread, &AddRet);
  ParOut = *(PARAMOUT *)AddRet;
  free((void *)AddRet);
  fprintf(stderr,"Fin du Processus : recupere : %lld : %s \n", 
    ParOut.ll, ParOut.nom);
  system("date +\"%H:%M:%S:%N\"");


  return EXIT_SUCCESS;
}

void *fonction_thread (void *pIn)
{
  PARAMIN ParIn = *(PARAMIN *)pIn;
  PARAMOUT *pParOut;

  pParOut = (PARAMOUT *)malloc(sizeof(PARAMOUT));
  pParOut->ll= 1000000;
  strcpy (pParOut->nom,"OK");


  fprintf(stderr,"Thread : pid %d, tid %d idlpt %ld\n",
    getpid(), syscall(SYS_gettid), pthread_self());
  fprintf(stderr,"Recupere : %d : %lf\n",ParIn.num, ParIn.dble);
  sleep(12);
  fprintf(stderr,"Thread : Terminaison : \n");
  system("date +\"%H:%M:%S:%N\"");
  pthread_exit ((void *)pParOut);
      
}

