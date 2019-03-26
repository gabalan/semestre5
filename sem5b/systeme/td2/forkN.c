#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
 System(char *commande){
	

}

int main (int argc, char *argv[]){ 
	int n = atoi(argv[1]);
	pid_t pids[n];
	for(int i = 0 ; i < n ; i++) {    
    		if( fork() == 0) {      
      			printf("le  fils %d  a pour pid  %d \n",i, getpid());
      			return 0; 
    		}
  	}
 
  	for(int i = 0 ; i < n ; i++)
		 waitpid(pids[i],NULL,0); 
 
  return 0;
}

