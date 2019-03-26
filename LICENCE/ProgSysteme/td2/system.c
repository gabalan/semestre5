#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void systeme(char * command){
printf("debut du fork\n");
pid_t pid=fork();
	if(pid==0){
	execl("/bin/sh","sh","-c",command,NULL);
	exit(0);
        }
	waitpid(pid,NULL,0);
printf("fin du fork\n");
}

int main( int argc, char *argv[]){
	printf("debut du main\n");
	systeme("ps --forest");
	systeme("ls -l");
	printf("fin du main\n");
	return 1;
}
