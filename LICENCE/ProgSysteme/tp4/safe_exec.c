#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>

#include "safe_exec.h"

sigjmp_buf *current;

void routine(int signo) {
    siglongjmp(*current,1);
}
int essayer(void (*fun)(void),int sig){//on peut aussi faire un tableau de jmpbuf et pour revenir on decremente l'indice
    sigjmp_buf new, *old;
    old = current;
    current = &new;
    if(sigsetjmp(current,1)==0) {
        struct sigaction s;
        s.sa_handler = routine;
        sigemptyset(&s.sa_mask);
        s.sa_flags=0;
        sigaction(sig,&s,NULL);
        fun();
        current = old;
        return 0;
    } else {
        current = old;
        return -1;
    }
}


/*
 * 
 */
void g() {
    volatile int *a = NULL;
    char x = *a;
}
void f() {
    int r;
    r = essayer(g,SIGSEGV);
    int *x = NULL;
    *x = 12;
    if(r) {
        printf("Erreur durant l'execution de g\n");
    } else {
        printf("L'execution de g s'est bien déroulé.\n");
    }
}
int main(int argc, char** argv) {
    int r;
    r = essayer(f,SIGSEGV);
    if(r) {
        printf("Erreur durant l'execution de f.\n");
    } else {
        printf("L'execution de f s'est bien déroulé.\n");
    }
    return (EXIT_SUCCESS);
}
