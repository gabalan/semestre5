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
  if(argc!=4){
    fprintf(stderr,"nombre de parametres incorrects");
  }
  int f1=open(argv[1],O_WRONLY | O_CREAT,0644);
  verifier(f1,"fichier");
  uint32_t position=strtoul(argv[2],NULL,10)*sizeof(uint32_t);
  int valeur=strtoul(argv[3],NULL,10);
  lseek(f1,position,SEEK_SET);
  write(f1,&valeur,sizeof(uint32_t));
  close(f1);
    return EXIT_FAILURE;
  }
