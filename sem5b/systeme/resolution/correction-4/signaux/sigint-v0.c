#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

struct sigaction act, oldact;

void myhandler(int signum) {
  if(signum == SIGINT)
    printf("Dans ton cul SIGINT !\n");
  
  // on restaure manuellement le traintant par défaut...
  sigaction(SIGINT, &oldact, NULL);  
}

int main() {

  act.sa_handler = myhandler; 
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  sigaction(SIGINT, &act, &oldact);

  while(1) {
    printf("coucou...\n");
    sleep(1);
  }
  
 return 0;
}
