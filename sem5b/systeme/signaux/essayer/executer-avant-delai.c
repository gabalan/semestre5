#define _GNU_SOURCE
#include <unistd.h>

#include "essayer.h"
#include <assert.h>
#include <signal.h>
#include <setjmp.h>
#include <stddef.h>
#include<stdio.h>
#include<stdlib.h>


int
executer_avant_delai( void (*fun)(void *), void *parametre, int delai_en_seconde)
{
  alarm(delai_en_seconde);
  essayer(fun,parametre,SIGALRM);
  alarm(0);
}
