#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main( int argc, char *argv[]){
  int tube[2];
  pipe(tube);
  pid_t pid=fork();
  int fd=open(argv[1],O_CREAT|O_WRONLY|O_TRUNC,0664);
  if(fd==-1)
    printf("error open\n");
  
  if(pid==0){//dans le fils
    close(tube[0]);
    dup2(tube[1],1);
    dup2(1,fd);
    execlp(argv[1],argv[1],NULL);
    perror(argv[1]);
    exit(1);
  }
  else{//dans le pere
    close(tube[1]);
    dup2(tube[0],0);
     execvp(argv[2],argv+2);
     perror(argv[2]);
     exit(1);
  }
  return 1;
}
