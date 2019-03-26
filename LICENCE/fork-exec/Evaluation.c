#include "Shell.h"
#include "Evaluation.h"

#include <stdio.h>

void
verifier(int cond, char *s)
{
  if (!cond)
    {
      perror(s);
      exit(1);
    }
}



int
evaluer_expr(Expression *e)
{
  return 1;
}
