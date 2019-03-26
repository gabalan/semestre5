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

void myhandler(int sig)
{
  printf("on vient de recevoir le signal %d (%s) %d fois\n",
         sig, strsignal(sig), ++tab[sig]);
}

int main(int argc, char *argv[])
{
  printf("pid: %d\n", getpid());

  /* on bloque tous les signaux */
  sigset_t fullmask;
  sigfillset(&fullmask);
  sigprocmask(SIG_BLOCK, &fullmask, NULL);

  int fpid = fork();

  if (fpid == 0)
  { /* FILS: emettre signaux */

    int ppid = getppid(); // mon père
    int k = atoi(argv[1]);

    for (int s = 2; s < argc; s++)
      for (int i = 0; i < k; i++)
      {
        kill(ppid, atoi(argv[s])); // envoi signal
      }

    // end it
    printf("I will kill daddy in 3 sec...\n");
    sleep(3);
    kill(ppid, 9);
  }

  else
  { /* PÈRE : recevoir signaux */

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

    /* on débloque la réception des signaux */
    sigset_t emptymask;
    sigfillset(&emptymask);
    sigprocmask(SIG_UNBLOCK, &emptymask, NULL);

    while (1)
    {
      pause(); // attente de signaux...
    }

    wait(NULL);
  }

  return 0;
}
