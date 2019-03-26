#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
//le pere dispose de p1 p0 ensuite une fois le fils créé il herite directement du meme file descriptor valide.
/* inr status
waitpid(pid,&status,0)
if(WIFEXITED(status))
*/
//waitpid a trois arg :le nom du pid, le status, les options.

void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}
int main (int argc, char *argv[])
{
  int p[2];
  pipe(p);
  if(fork() == 0){
    char c;
    while(read(0,&c,1)>0){
      write(p[0],&c,1);
    }
  }
  else{
  //  wait(NULL);
  // close(p[1]);
  char buf[100];
  printf("%s\n","je suis le pere" );
    read(p[1],&buf,100);
  }
  return 0;
}
