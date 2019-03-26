#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/* SA_RESETHAND = restore the signal action to the default state
 * once the signal handler has been called (ONE SHOT)
 */

struct sigaction act;

void myhandler(int signum) {
  if(signum == SIGINT)
    printf("Dans ton cul SIGINT !\n");
}

int main() {
  
  act.sa_handler = myhandler; 
  act.sa_flags = SA_RESETHAND; 
  sigemptyset(&act.sa_mask);
  sigaction(SIGINT, &act, NULL);
  
  while(1) {
    printf("coucou...\n");
    sleep(1);
  }
  
  return 0;
}

