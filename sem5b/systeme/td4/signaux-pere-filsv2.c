// compilation: gcc -std=c99 signaux-pere-fils.c
// test: ./a.out 100 1 2 3 4 5 6

#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define NSIGNORT 32
int tab[NSIGNORT];

void myack(int sig) {}

void myhandler(int sig)
{
  printf("on vient de recevoir le signal %d (%s) %d fois\n",
         sig, strsignal(sig), ++tab[sig]);
}

int main(int argc, char *argv[])
{

  printf("pid: %d\n", getpid());

  // par défaut, on bloque tous les signaux (hérité par le fils)
  sigset_t fullmask;
  sigfillset(&fullmask);
  sigprocmask(SIG_BLOCK, &fullmask, NULL);

  int fpid = fork();

  if (fpid == 0)
  { /* FILS: emettre signaux */

    struct sigaction act;
    act.sa_handler = myack;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGUSR1, &act, NULL);

    int ppid = getppid(); // mon père
    int k = atoi(argv[1]);

    // on débloque SIGUSR1 uniquement
    sigset_t ackmask;
    sigfillset(&ackmask);
    sigdelset(&ackmask, SIGUSR1);

    for (int s = 2; s < argc; s++)
      for (int i = 0; i < k; i++)
      {
        kill(ppid, atoi(argv[s])); // envoi signal
        sigsuspend(&ackmask);      // attente ack
      }

    // I will kill daddy in 3 sec...
    sleep(3);
    kill(ppid, 9);
  }

  else
  { /* PÈRE : recevoir signaux */

    // sleep(1); // debug

    // installation du handler pour tous les signaux non RT
    struct sigaction act;
    act.sa_handler = myhandler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);

    for (int sig = 1; sig < NSIGNORT; sig++)
    {
      sigaction(sig, &act, NULL);
      tab[sig] = 0;
    }

    sigset_t emptymask;
    sigemptyset(&emptymask);
    while (1)
    {
      sigsuspend(&emptymask); // attente de signaux (en les débloquant tous)...
      kill(fpid, SIGUSR1);    // envoie ack
    }

    wait(NULL);
  }

  return 0;
}
