#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUFFIXE ".idx"
void afficher(int fd){
  char c;
  while(read(fd,&c,1)>0){
    write(1,&c,1);
    if(c=='\n')return;
  }
}
void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]){
  verifier(argc == 3, "il faut deux paramètres.");

  // construire le chemin au fichier index
  int l = strlen(argv[1]) ;
  char idx_filename[l + strlen(argv[1]) + 1];

  strncpy(idx_filename, argv[1], l);
  strcpy(idx_filename + l, SUFFIXE);
  char *filename =argv[1];
  int fd=open(filename,O_RDONLY);
  int idx_fd=open(idx_filename,O_RDONLY);
  int numero=atoi(argv[2]);//num de la ligne
  if(numero>0){
  int idx_offset=(numero-1)*sizeof(int);//probleme cas numero=0
  lseek(idx_fd,idx_offset,SEEK_SET);
  int position;
  read(idx_fd,&position,sizeof(int));
  int offset=position;
  lseek(fd,offset,SEEK_SET);
}
  afficher(fd);
  close(fd);
  close(idx_fd);


  return EXIT_SUCCESS;
}
