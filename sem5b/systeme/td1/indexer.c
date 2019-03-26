#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUFFIXE ".idx"
#define BUF_SIZE 2048


void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]){
  verifier(argc == 2, "il faut un paramètre.");
  // construire le chemin au fichier index
  int l = strlen(argv[1]) ;
  char idx_filename[l + strlen(argv[1]) + 1];
  strncpy(idx_filename, argv[1], l);
  char *fichier=strcpy(idx_filename + l, SUFFIXE);
  char *filename=argv[1];
  int idex_fd=open(idx_filename,O_WRONLY|O_CREAT|O_TRUNC,0644);
  int fd=open(filename,O_RDONLY);
  char c;
  int compte=0;int row=0;
  while(read(fd,&c,1)>0){
    if(c=='\n'){
      write(idex_fd,&compte,sizeof(int));
    }
    compte=compte+1;
  }
  close(idex_fd);
  close(fd);

  return EXIT_SUCCESS;
}
