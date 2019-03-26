#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


#define NSIGNORT 34
int tab[NSIGNORT];
sigset_t masque;


void handler_qui_fait_rien(int sig) {
 }


int emetteur(int pere, int argc, char * argv[]) {
  int k = atoi(argv[1]);
  
  struct sigaction act;
  act.sa_handler = handler_qui_fait_rien; 
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  sigaction(SIGUSR1, &act, NULL);

  
  for(int i = 0 ; i < k ; i++) 
    for(int j = 2; j < argc; j++){
      kill(pere,atoi(argv[j]));
      pause();
  }

  kill(pere,9);

  return 0;
}





void myhandler(int sig) {
  printf("on vient de recevoir le signal %d (%s) %d fois\n",
	 sig, strsignal(sig), ++tab[sig]);
}


int recepteur(int fils) {

  // installation du handler pour tous les signaux non RT
  struct sigaction act;
  act.sa_handler = myhandler; 
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  
  for(int sig = 0 ; sig < NSIGNORT ; sig++) {
    sigaction(sig, &act, NULL);
    tab[sig] = 0;
  }
    
  while(1) {
    pause();
    kill(fils,SIGUSR1);
  }
  
  return 0;
}


int main(int argc, char *argv[]){


  pid_t pid = fork();

  if (pid == 0)
    emetteur(getppid(),argc,argv);
  else
    recepteur(pid);  
}
