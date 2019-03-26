
#include "essayer.h"

#include <assert.h>
#include <signal.h>
#include <setjmp.h>
#include <stddef.h>



#define MAXJMP 1000

typedef void (*func_t)(void);

static int level = 0;
static jmp_buf jmp[MAXJMP];

static void handler(int sig)
{
  siglongjmp(jmp[level], sig);
}

int essayer(void  (*f)(void*), void *p, int sig)
{
  struct sigaction sa, old_sa;
  sigset_t set;
  int signal_recu;

  sa.sa_handler = handler;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  sigaction(sig, &sa, &old_sa);

  level++; // on "empile" un nouveau ctxt
  assert(level < MAXJMP);
  
  signal_recu = sigsetjmp(jmp[level], 1); 
  if(signal_recu == 0)
    f(p);
  
  level--; // le ctxt a été dépilé
  sigaction(sig, &old_sa, NULL);
  
  if (signal_recu > 0 && signal_recu != sig) // on ne traite pas ce signal ici
    raise(signal_recu);                      // on l'émet à nouveau

  return signal_recu;   // retoune 0 si pas de signal, sig autrement   
}
