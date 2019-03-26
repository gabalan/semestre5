#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
  int tube[2];
  pipe(tube);
  char c;
  for(int i=0;;i++){
    write(tube[1],&c,sizeof(char));
    printf("%d\n",i);
  }
  return 0;
}
