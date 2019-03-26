#include <sys/types.h>
#include<errno.h>
#include<unistd.h>
#include <stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <time.h>

int main(){
  pid_t pid;
  pid=fork();
  if(pid==0){
  printf("je m'appellle  %d et je suis le fils de %d\n",(int)getpid(),(int)getppid() );
}
else{
 wait(NULL);
  printf("je m'appellle  %d et je suis le pere de %d\n",getpid(),pid);
}
  return EXIT_SUCCESS;
}
