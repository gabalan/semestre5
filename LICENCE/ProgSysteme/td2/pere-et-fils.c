#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char * argv []){

  pid_t pid=fork();
  
  if(pid==0){
    //wait(&pid); le message du pere toujours en premier
    printf("je m'appelle %d et je suis le fils de %d\n",getpid(),getppid());
   
  }
  else{
    getchar();
    printf("je m'appelle %d et je suis le pere de %d\n",getpid() ,pid);
  }
  return 0;
}
