#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
  int p[2];
  pipe(p);

  if(fork()) { /* père */
    close(p[1]);
    dup2(p[0], 0);
    close(p[0]);
    execlp("tee", "tee", argv[1], NULL);
    exit(EXIT_FAILURE);
  }
  else {
    close(p[0]);
    dup2(p[1], 1);
    close(p[1]);
    execvp(argv[2], argv+2);
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
