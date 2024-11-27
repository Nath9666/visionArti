#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

void *fonction_thread (void *);
int main (int argc, char **argv)
{
  int ret;
  pthread_t thread;
  double dParam = 3.14;
  void *AddRet;
  long long llPramRet;

  fprintf(stderr, "Processus : Pid = %d, Ppid = %d\n", getpid(), getppid());

  /* --- Creation du Thread --- */
  if ((ret = pthread_create (&thread, NULL, fonction_thread, (void*)(&dParam))) 
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
  llPramRet = *(long long *)AddRet;

  fprintf(stderr,"Fin du Processus : recupere : %lld \n", 
    llPramRet);
  system("date +\"%H:%M:%S:%N\"");


  return EXIT_SUCCESS;
}

void *fonction_thread (void *pIn)
{
  double dParamTh = *(double *)pIn;
  // long long llParamTh  = 1000000;
 long long *pllParamTh;

  pllParamTh = (long long *)malloc(sizeof(long long));
  *pllParamTh = 1000000;


  fprintf(stderr,"Thread : pid %d, tid %d idlpt %ld\n",
    getpid(), syscall(SYS_gettid), pthread_self());
  fprintf(stderr,"Parametre recupere : %lf\n",dParamTh);
  sleep(12);
  fprintf(stderr,"Thread : Terminaison : Passage %lld \n",
    *pllParamTh);
  system("date +\"%H:%M:%S:%N\"");
  pthread_exit ((void *)pllParamTh);
  // pthread_exit ((void *)&llParamTh);    
}

