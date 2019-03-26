#define _GNU_SOURCE
#include <unistd.h>

#include "essayer.h"


struct param
{
  int delai;
  void (*fun)(void*);
  void *parametre;
};
  
void
exec_avec_alarm(void *parametre)
{
  struct param *p = (struct param *) parametre; 
  alarm(p->delai);
  p->fun(p->parametre);
  alarm(0);
}


int
executer_avant_delai( void (*fun)(void *), void *parametre, int delai_en_seconde)
{
  struct param p = {delai_en_seconde, fun, parametre};
  return essayer(exec_avec_alarm, &p, SIGALRM);
}
