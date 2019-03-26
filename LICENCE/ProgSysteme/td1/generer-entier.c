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
  int fd, entier;
 
  fd=open("entier", O_WRONLY|O_CREAT|O_TRUNC,0660);
  for(int i=0;i<atoi(argv[1]);i++){
    write(fd,&i,sizeof(int));
    }
   close(fd);
 
 
  return EXIT_SUCCESS;
}



