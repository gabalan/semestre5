#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
  int p[2];
  pipe(p);
  int pid =fork();
  if(pid==0){
    close(p[0]);
    dup2(p[1],1);
    execvp(argv[2],argv+2);
    perror("execvp");
    exit(EXIT_FAILURE);

  }/*tee*/
    if(fork()==0){
      close(p[1]);
      dup2(p[0],0);
      close(p[0]);
      execlp("tee","tee",argv[1],NULL);
      exit(EXIT_FAILURE);
    }
    close(p[0]);
    close(p[1]);
    wait(NULL);
    wait(NULL);
    return EXIT_SUCCESS;
}
