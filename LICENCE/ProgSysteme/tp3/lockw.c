#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
  int tube[2];
  pipe(tube);

  close(tube[0]);
   write(tube[1],"bonjour",7);
   perror("ser");
	char c;
  for(int i=0;i<10;++i){
    read(tube[0],&c,sizeof(char));
	 printf("%c\n",c);
  }
  printf("finduprogramme\n");
  return 1;

}
