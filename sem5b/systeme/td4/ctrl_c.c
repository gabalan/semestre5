#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
/*sigaction  prend trois param  :le num de signal,adr d'une strucutre sigaction,NULL

sigaction(SIGINT,&act,NULL)
*/

void handler(int s){
  printf("ctrl_c %s\n",strsignal(s));
}
int main (int argc, char *argv[])
{
  struct sigaction act;
    act.sa_handler=handler;
    act.sa_flags=0;
    sigemptyset(&act.sa_mask);
    struct sigaction old_act;

//  sigaction(SIGINT,&act,&old_act);
//  puase();
  sigaction(SIGINT,&act,NULL);
  while (1) pause();
  pause();
  return EXIT_SUCCESS;
}
