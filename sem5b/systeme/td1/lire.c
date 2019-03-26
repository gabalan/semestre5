#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include<sys/stat.h>
#include <arpa/inet.h>
void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}


int
main(int argc, char **argv)
{
  if(argc!=3){
    fprintf(stderr,"nombre de parametres incorrects");
  }
  int f1=open(argv[1],O_WRONLY);
  verifier(f1,"fichier");
  uint32_t position=strtoul(argv[2],NULL,10)*sizeof(uint32_t);
  printf("%d\n",position );
  uint32_t valeur;
  lseek(f1,position,SEEK_SET);
  read(f1,&valeur,sizeof(uint32_t));
  printf("valeur=%u\n",valeur);
  close(f1);
    return EXIT_FAILURE;
    //redirection de 1.5
    /*
    int fd=open("log",O_WRONLY|O_CREAT,0644);
    int dir=dup2(2,fd);
  }
