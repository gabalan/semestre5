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
 
  if (argc != 4)
    {
      fprintf(stderr,"%s : <input file name>"
	      "<nom fichier> <position d'ecriture> <valeur a ecrire> \n", argv[0]);
      return EXIT_FAILURE;
    }
  int fd,fichier,position,valeur;
  
  fichier=atoi(argv[1]);
  position=atoi(argv[2]);
  valeur=atoi(argv[3]);
  
  fd=open("fichier", O_WRONLY|O_CREAT,0660);
   if(fd==-1){
    printf("error\n");
    exit(-1);
   }  
  lseek(fd,position*sizeof(int),SEEK_SET);
  write(fd,&valeur,sizeof(int));
    
   close(fd);
  
   return EXIT_SUCCESS;
}
