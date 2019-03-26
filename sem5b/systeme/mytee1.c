#define  _GNU_SOURCE
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>



void testErreur(int assertion){
  if(assertion){
    perror("erreur");
    exit(EXIT_FAILURE);
  }
}
int main(int argc,int *argv[]){
  if(argc!=3){
    fprintf(stderr, "le nombre de parametres incorrect" );
    return EXIT_FAILURE;
  }
  char const* c=argv[1];
  int in=write(STDOUT_FILENO,c,strlen(c));
  if(in<0){
    perror("echec de l'ecriture");
  }
//  char *chaine=argv[2];
  int input=open(argv[2],O_WRONLY);
  /*testErreur(input<0);
  ftruncate(input,0);
  int in2=write(argv[2],c,strlen(c));
  if(in2<0){
    perror("echec de l'ecriture");
  }*/
  strcpy(, );
  close(input);
  return EXIT_SUCCESS;
}
