#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  int pid = atoi(argv[1]);
  int k = atoi(argv[2]);

  printf("envoi de %d signaux (SIGINT,SIGUSR1,SIGUSR2) a %d\n", k, pid);
  
  for(int i = 0 ; i < k ; i++) {
    kill(pid,SIGINT);
    kill(pid,SIGUSR1);
    kill(pid,SIGUSR2);
  }


  printf("presser une touche pour tuer %d... \n",pid);
  char c = getchar();  
  kill(pid,9);

 return 0;
}
