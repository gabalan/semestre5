#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>


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
    return EXIT_FAILURE;
  }/*char c
while(read(f1,&c,1)>0){
write(fd2,&c,1)
}  */
int f1,f2,r,w;
f1=open(argv[1],O_RDONLY);
f2=open(argv[2],O_WRONLY|O_CREAT | O_TRUNC,0644);
verifier(f1,"open de f1");
verifier(f2,"open f2");

int buffer_size=atoi(argv[3]);
//char buf[buffer_size];--->marche mais avec une taille trop grande il y'aura une segmentation fault
char *buf=malloc(buffer_size);
do{
  r=read(f1,buf,buffer_size);
  w=write(f2,buf,r);
}while(r>0);
close(f1);
close(f2);
  return EXIT_SUCCESS;
}
/*VARIANTE AVEC fcopy.c*/

/* FILE* file1=fopen(arg[1],"r");
FILE* file2=fopen(argv[2],"r");
while(fread(&c,1,1,file1)>0){
fwrite(&c,1,1,file2);
}
fclose(file1
fclose(file2))*/
