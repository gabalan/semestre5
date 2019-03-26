#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


void verifier(int i, char *s)
{
  if (!i) {
    perror (s);
    exit (EXIT_FAILURE);
  }
}

void quelques_prints (void)
{
  printf ("Juste");
  printf (" histoire");
  printf (" de tester...\n");
  printf ("...que la redirection");
  printf (" marche !\n");
}

void rediriger_vers (void (*f)(void), char *file){
  int stdout_copy=dup(1);
   int fd = open(file, O_WRONLY|O_CREAT|O_APPEND, 0644);
   int d=dup2(fd,1);
   f();
   close(d);
   dup2(stdout_copy,1);
   close(stdout_copy);
   close(fd);
}
int main(int argc, char *argv[])
{
  printf ("*** DEBUT ***\n");

  rediriger_vers (quelques_prints, "sortie.txt");

  printf ("*** FIN ***\n");

  return EXIT_SUCCESS;
}
