#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>


void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}
int main (int argc, char *argv[])
{
  // création d'un nouveau processus fils...
  int pid = fork();

  if(pid == 0) { // fils
    int fd = open("/tmp/toto", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd < 0) { perror("open"); exit(EXIT_FAILURE);}
    dup2(fd,STDOUT_FILENO); // redirection de la sortie standard dans le fichier
    close(fd);
    execlp(argv[1],argv[1],NULL); // cmd1 remplace le processus fils
    perror("exec cmd1"); exit(EXIT_FAILURE);
  }
  else { // pére
    wait(NULL); // j'attend la fin de mon fils...
    int fd = open("/tmp/toto", O_RDONLY);
    if(fd < 0) { perror("open"); exit(EXIT_FAILURE);}
    dup2(fd,STDIN_FILENO); // redirection de l'entrée du programme
    close(fd);
    unlink("/tmp/toto"); // suppression du fichier à la fin du programme...
    execvp(argv[2],argv+2); // cmd2 remplace le processus principal
    perror("exec cmd2"); exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
