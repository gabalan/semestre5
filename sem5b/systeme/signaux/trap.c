#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>

volatile char *a=NULL;
volatile char b='x';
//LE FAIT D'AVOIR MIS A JOUR UNE VARIABLE DANS LA MEMOIRE NE LA CHANGE PAS DANS LE REGISTRE
//le x=&a enregistre dans un REGISTRE d'abord
// %eax=NULL ;;;; mov (%eax)=%ebx


void traitant(int s)
{
  printf("signal %d\n", s);
  a = &b;
}

int main()
{
  struct sigaction s;
  char x;

  s.sa_handler = traitant;
  sigemptyset(&s.sa_mask);
  s.sa_flags=0;
  sigaction(SIGSEGV,&s,NULL);

  x = *a;

  printf("fin %c\n",x);
  return 0;
}
