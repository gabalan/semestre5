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
float cpt =0;

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
  {"sleep","1",NULL}, 
  {"sleep","2",NULL}, 
  {"sleep","4",NULL}, 
  {"sleep","4", NULL} 
};


void afficher_etat()
{
  int i;
  
  for ( i=0;i<NCOMMANDES;i++)
    {
      switch(etat_tableau[i]->etat)
	{
	case 3:
	  printf("%d : Stoppé %s(%s)\n",etat_tableau[i]->pid,etat_tableau[i]->commande,etat_tableau[i]->arg);
	  break;

	case 2:
	  printf("%d : Continué %s(%s)\n",etat_tableau[i]->pid,etat_tableau[i]->commande,etat_tableau[i]->arg);
	  break;

	case 1:
	  printf("%d : En cours %s(%s)\n",etat_tableau[i]->pid,etat_tableau[i]->commande,etat_tableau[i]->arg);
	  break;
	  
	case 0:
	  printf("%d : Terminé %s(%s)\n",etat_tableau[i]->pid,etat_tableau[i]->commande,etat_tableau[i]->arg);
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

void traitant_SIGCHLD()
{
   int fils;
   int status;
  //Si 2 mort en meme temps: 1 signal mais 2 wait pid.
   while((fils= waitpid(-1, &status, WNOHANG  | WUNTRACED | WCONTINUED)) >0)
    {
      int i=0;
      while(i<NCOMMANDES)
	{
	  if(etat_tableau[i]->pid == fils)
	    {
	      if (WIFEXITED(status)) {
		etat_tableau[i]->etat=0; 
	      } else if (WIFSIGNALED(status)) {
		etat_tableau[i]->etat=0; 
	      } else if (WIFSTOPPED(status)) {
		etat_tableau[i]->etat=3; 
	      } else if (WIFCONTINUED(status)) {
		etat_tableau[i]->etat=2; 
	      }
	     break;
	    }
	  i++;
	}
    }
}


int
main(int argc, char *argv[])
{
  pid_t cpid, w;
  int status;

  struct sigaction sa,sa2;
  sa.sa_handler= traitant_SIGCHLD;
  sa.sa_flags=SA_RESTART;
  sigemptyset(&sa.sa_mask);


  sigaction(SIGCHLD,&sa,NULL);

  sigset_t masque;
  sigemptyset(&masque);
  sigaddset(&masque,SIGCHLD);
  
  int i;
  /* Lancement */
  for(i=0; i < NCOMMANDES; i++)
    {
      sigprocmask(SIG_BLOCK,&masque,NULL);
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
      etat_tableau[i]->etat=1;
      sigprocmask(SIG_UNBLOCK,&masque,NULL);
    }

  /* Analyse */

  for(int cpt = 1; reste_commande(); cpt++ )
    {
      char buf[1024];
      printf("iteration %d\n",cpt);
      
      int r = read(0,buf,1024);     
      if (r == -1)
	perror("read");
      printf("-------- Liste des zommbies ------- \n");
      system("ps -eo pid,ppid,state | awk '$3==\"Z\"'");
      printf("-------- Fin liste zommbies ------- \n\n");
      afficher_etat(); 
    }
  
  afficher_etat();
  printf("Tous les processus se sont terminés !\n");

  exit(EXIT_SUCCESS);
}
