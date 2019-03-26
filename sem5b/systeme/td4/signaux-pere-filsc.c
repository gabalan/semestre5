#define XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define NSIGNORT 32

int emetteur(int pere, int argc, char * argv[]) {
  int k = atoi(argv[1]);

  for(int i = 0 ; i < k ; i++)
    for(int j = 2; j < argc; j++){
      kill(pere,atoi(argv[j]));
  }

  //kill(pere,9);
  return 0;
}

int tab[NSIGNORT];
void handler(int s){
  tab[s]++;
  printf("signal %d (%d fois ) \n",s,tab[s]);
}
int recepteur(int fils) {
  printf("récepteur : %d\n", getpid());

  // installation du handler pour tous les signaux non RT
  struct sigaction act;
    act.sa_handler=handler;
    act.sa_flags=0;
    sigemptyset(&act.sa_mask);


  for(int sig = 0 ; sig < NSIGNORT ; sig++) {
    //sigaction( , , );
    sigaction(sig,&act,NULL);
  }
  sigset_t emptyset;
  sigemptyset(&emptyset);
  sigprocmask(SIG_SETMASK,&emptyset,NULL);

  while(1)
    pause();

  return 0;
}


int main(int argc, char *argv[]){
  sigset_t set,old_set;
  sigfillset(&set);
  sigprocmask(SIG_SETMASK,&set,NULL);
  pid_t pid = fork();
  if (pid == 0)
    emetteur(getppid(),argc,argv);
  else
    recepteur(pid);
}
