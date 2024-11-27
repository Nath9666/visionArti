#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

int main (int argc, char **argv)
{
  int oldCpu, newCpu;
  oldCpu = sched_getcpu();
  fprintf(stderr,"Nombre Cpu : %d\n",sysconf(_SC_NPROCESSORS_ONLN));
  fprintf(stderr, "Processus %d de pere %d sur coeur %d\n", 
    getpid(), getppid(),oldCpu );
  
  for (;;)
  {
    newCpu = sched_getcpu();
    if (newCpu != oldCpu)
    {
      fprintf(stderr, "Processus %d : migration %d => %d\n",
        getpid(),oldCpu, newCpu);
      oldCpu = newCpu;
    }
  }
  return EXIT_SUCCESS;
}