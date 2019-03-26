#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

/* bash -c "ls -l"*/
int  System(char *commande){
	pid_t pid;
	pid=fork();
	if(pid==0){
	execlp("bash","bash" "-c",commande,NULL);
	exit(EXIT_FAILURE);/* s'execute ssi le exec echoue */
	}
	int status;
	waitpid(pid,&status,0);
return status;

}

int main (int argc, char *argv[]){
	System("ls -l");
 
  return EXIT_SUCCESS;
}
/*exo4 on utilise execvp*/
