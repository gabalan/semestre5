
#include "essayer.h"

#include <assert.h>
#include <signal.h>
#include <setjmp.h>
#include <stddef.h>
#include<stdio.h>
#include<stdlib.h>

jmp_buf env;
typedef void (*func_t)(void);

void handler(int sig){
  longjmp(env,1);
}

int essayer(void  (*f)(void*), void *p, int sig)
{
  struct sigaction act, old;
 act.sa_flags = 0;
 act.sa_handler = handler;
 sigemptyset(&act.sa_mask);
 sigaction(sig, &act, &old);
 int r=setjmp(env);
    if(r==0){
      f(p);
    }
    sigaction(sig,&old,NULL);
    return r;
}
