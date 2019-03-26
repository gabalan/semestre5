#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void 
perror_and_exit_whenever(int assertion)
{
  if (assertion)
    {
      perror("");
      exit(EXIT_FAILURE);
    }
}


int main(int argc,char ** argv){
 
  if (argc != 2)
    {
      fprintf(stderr,"%s : <input file name>"
	      " <un entier> \n", argv[0]);
      return EXIT_FAILURE;
    }
  int Fin,taille;
  Fin=open(argv[1],O_RDONLY);
  taille=lseek(Fin,0,SEEK_END);
  lseek(Fin,0,SEEK_SET);
  
  for(int i=0;i<taille;i++){
  read(Fin,&i,sizeof(int));
  printf("%d\n",i);
  }
}
