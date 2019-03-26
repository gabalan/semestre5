#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include<dlfcn.h>
#include<string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv){
  pid_t pid;
	pid=fork();
	if(pid==0){
    alarm(5);
	execvp(argv[1],argv+1);
	exit(EXIT_FAILURE);/* s'execute ssi le exec echoue */
	}
	int status;
	waitpid(pid,&status,0);
   printf("*** code de retour : %s\n", strsignal(status));
return status;

}
