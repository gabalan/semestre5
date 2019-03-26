#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define NSIGNORT 34
int tab[NSIGNORT];
struct sigaction act;
sigset_t masque;

void myhandler(int sig) {
  printf("on vient de recevoir le signal %d (%s) %d fois\n",
	 sig, strsignal(sig), ++tab[sig]);
}


int main() {
  printf("PID %d\n",getpid());

  // exemple d'utilisation de sigprocmask pour bloquer SIGUSR1
  sigemptyset(&masque);
  sigaddset(&masque, SIGUSR1);
  sigprocmask(SIG_BLOCK, &masque, NULL);

  // installation du handler pour tous les signaux non RT
  act.sa_handler = myhandler; 
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  
  for(int sig = 0 ; sig < NSIGNORT ; sig++) {
    sigaction(sig, &act, NULL);
    tab[sig] = 0;
  }
    
  printf("on bloque SIGUSR1...\n");

  while(1) {
    pause(); // attente de signaux...
    printf("retour de pause\n");
    printf("on debloque SIGUSR1...\n");
    sigprocmask(SIG_UNBLOCK, &masque, NULL);
  }
    
 return 0;
}
