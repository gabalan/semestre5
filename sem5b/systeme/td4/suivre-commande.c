#define _GNU_SOURCE

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

#define NCOMMANDES 4

struct etat
{
  pid_t pid;
  char commande[10];
  char arg[10];
  int etat;
};

typedef struct etat* etat;


etat etat_tableau[NCOMMANDES];


char *commandes[NCOMMANDES][10]={
  {"sleep","0",NULL},
  {"sleep","3",NULL},
  {"sleep","4",NULL},
  {"sleep","5", NULL}
};


void modifier_etat(pid_t pid, int status){
  int i;
  for(i=0; i < NCOMMANDES ; i++)
    if(etat_tableau[i]->pid == pid)
      break;

  if (WIFEXITED(status)) {
    etat_tableau[i]->etat=0;
  } else if (WIFSIGNALED(status)) {
    etat_tableau[i]->etat=0;
  } else if (WIFSTOPPED(status)) {
    etat_tableau[i]->etat=3;
  } else if (WIFCONTINUED(status)) {
    etat_tableau[i]->etat=2;
  }
}



void afficher_etat()
{
  int i;

  for ( i=0;i<NCOMMANDES;i++)
    {
      switch(etat_tableau[i]->etat)
	{
	case 3:
	  printf("%d : Stopped %s(%s)\n",etat_tableau[i]->pid,etat_tableau[i]->commande,etat_tableau[i]->arg);
	  break;

	case 2:
	  printf("%d : Continued %s(%s)\n",etat_tableau[i]->pid,etat_tableau[i]->commande,etat_tableau[i]->arg);
	  break;

	case 1:
	  printf("%d : Running %s(%s)\n",etat_tableau[i]->pid,etat_tableau[i]->commande,etat_tableau[i]->arg);
	  break;

	case 0:
	  printf("%d : Terminated %s(%s)\n",etat_tableau[i]->pid,etat_tableau[i]->commande,etat_tableau[i]->arg);
	  break;

	}
    }
  printf("\n");
}

int reste_commande()
{
  int i;

  for (i=0;i<NCOMMANDES;i++)
    {
      if(etat_tableau[i]->etat)
	return 1;
    }
  return 0;
}


void lancer_commandes()
{
 int i;
 pid_t cpid;

  /* Lancement */
  for(i=0; i < NCOMMANDES; i++)
    {
      cpid = fork();
      if (cpid == -1) {
	perror("fork");
	exit(EXIT_FAILURE);

      }

      if (cpid == 0) {
	execvp(commandes[i][0],commandes[i]);
	perror("execvp");
	abort();
      }

      etat_tableau[i]=malloc(sizeof(struct etat));
      etat_tableau[i]->pid=cpid;
      strcpy(etat_tableau[i]->commande,commandes[i][0]);
      strcpy(etat_tableau[i]->arg,commandes[i][1]);
      etat_tableau[i]->etat=1; /* en cours */
    }
}
void myhandler(int sig)
{
  printf("CCCCCCCCCCCCCCCCCC\n");
  pid_t w;
  int status;
  w = waitpid(0, &status, WUNTRACED | WCONTINUED | WNOHANG);//WAIT NON BLOQUANT .ON EST PAS OBLIGER D'ATTENDRE LA MORT D'UN FILS.
  printf("pid = %d\n", w);
  if (w > 0){
     modifier_etat(w,status);
  }
}
void myack(int sig) {}
int
main(int argc, char *argv[])
{
  struct sigaction act;
  act.sa_handler = myack;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  sigaction(SIGUSR1, &act, NULL);
  char buf[1024];

  lancer_commandes();

  for(int cpt = 1; reste_commande(); cpt++ )
    {
      printf("iteration %d\n",cpt);
      int r = read(0,buf,1024);
      if (r == -1)
	     perror("read");
      printf("-------- Liste des zommbies ------- \n");
      //system("ps -eo pid,ppid,state,cmd | awk '$3==\"Z\"'");
      printf("-------- Fin liste zommbies ------- \n\n");
      afficher_etat();

    }

  printf("Tous les processus se sont terminés !\n");
  afficher_etat();
  exit(EXIT_SUCCESS);
}
