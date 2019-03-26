#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  int fd = open("error", O_WRONLY|O_CREAT|O_APPEND, 0644);
  dup2(fd, 0); close(fd);
  printf("hello on stdout\n");
  fprintf(stderr, "hello on stderr\n");
  return EXIT_SUCCESS;
}
