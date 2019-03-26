#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc,char ** argv){
 
  if (argc != 3)
    {
      fprintf(stderr,"%s : <input file name>"
	      "<nom fichier> <position de lecture> \n", argv[0]);
      return EXIT_FAILURE;
    }
  int fd,fichier,position,valeur;
  
  fichier=atoi(argv[1]);
  position=atoi(argv[2]);

  
  fd=open("fichier", O_WRONLY,0660);
   if(fd==-1){
    printf("error fichier inexistant\n");
    exit(-1);
   }  
 
  lseek(fd,position*sizeof(int),SEEK_SET);
  read(fd,&position,SEEK_CUR);
  write(fd,&position,sizeof(int));


 
   close(fd);
  
   return EXIT_SUCCESS;
}
