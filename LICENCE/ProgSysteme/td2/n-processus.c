#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char argv []){
  pid_t pid;
  
   if (argc != 2)
    {
      fprintf(stderr,"%s : <input file name>" " <un entier> \n", argv[0]);
      return EXIT_FAILURE;
    }
    
   int n=atoi(argv[1]);
   
   for(int i=0;i<n;i++){
     
	pid=fork();
	if(pid==0){
	  printf("processus numero %d \n",i);
	}
	else{
	  wait(NULL);
	  printf("processus numero killed %d \n",i);
	}
	}
      return EXIT_SUCCESS;
}
