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


int 
main(int argc, char **argv)
{
  
  int power;
  size_t buffer_size;
  
 
  if (argc != 4)
    {
      fprintf(stderr,"%s : <input file name>"
	      " <output filename> <log2 of buffer length> \n", argv[0]);
      return EXIT_FAILURE;
    }

  

  
  power = strtoul(argv[3], NULL, 10);
  buffer_size = 1 << power;
char * buffer=malloc(buffer_size);

  char c;
  int Fin,Fout;
  perror_and_exit_whenever(Fin=open(argv[1],O_RDONLY)==-1);
 
  perror_and_exit_whenever(Fout=open(argv[2], O_WRONLY|O_CREAT,0660)==-1);//O_SYNC

  while(read(Fin,buffer,buffer_size)>0);
	write(Fout,buffer,buffer_size);
	
    
   close(Fin);
   close(Fout);
   free(buffer);
 
  return EXIT_SUCCESS;
}
