#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

sigjmp_buf buf;

void traitant(int signo) {
    siglongjmp(buf,1);
}
int executer_avant_delai( void (*fun)(void *), void *parametre, int delai){
    if(sigsetjmp(buf,1)==0) {
        struct sigaction s;
        s.sa_handler = traitant;
        s.sa_flags = 0;
        sigemptyset(&s.sa_mask);
        //Receive SIGALRM
        sigaction(SIGALRM,&s,NULL);
        alarm(delai);
	alarm(0);
	fun(parametre);
	printf("ok\n");
        return 1;
    } else {
      printf("fin de la fonction\n");
        return 0;
    }
    
}


void 
oui_ou_non(void *reponse)
{
  char c = getchar(); getchar();
  *(int *)reponse = c == 'o' || c == 'O' ;
}
 
int main()
{

  int rep ;
  
  printf(" oui ou non ? ");

  if( executer_avant_delai(oui_ou_non,&rep,5))
    printf("reponse : %c\n", rep == 1 ? 'O' : 'N');
  else 
    printf("pas de réponse\n");
  
  printf(" oui ou non ? ");
  if( executer_avant_delai(oui_ou_non,&rep,5))
    printf("reponse : %c\n", rep == 1 ? 'O' : 'N');
  else 
    printf("pas de réponse\n");

  return EXIT_SUCCESS;

}
