#define  _GNU_SOURCE
#define MAXI 10
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdbool.h>

#define SUFFIXE ".idx"

void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}


void testErreur(int assertion){
  if(assertion){
    perror("erreur");
    exit(EXIT_FAILURE);
  }
}
int main(int argc,char *argv[]){
  /*if(argc!=3){
    fprintf(stderr, "le nombre de parametres incorrect" );
    return EXIT_FAILURE;
  }
  int out=3;
  int in=3;
  int r=3;
  int fd=open(argv[1],O_WRONLY | O_CREAT,0644);
  do{
    char buf[MAXI];
    r=read(0,buf,MAXI);
    in=write(fd,buf,r);
    out=write(1,buf,r);

  }while(r>0);*/
  int fd=open(argv[1],O_WRONLY | O_CREAT,0644);
verifier(fd>0,"open");
char c;
while(read(0,&c,1)>0){
  write(1,&c,1);
  write(fd,&c,1);
}
  close(fd);
return EXIT_SUCCESS;
}
