#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define TAILLE_MESSAGE 256 /* Correspond à la taille de la chaîne à écrire */
/* exo34
lecture fermer :il y'aura un sigpipe
ecrite feermer: lire jusu'a ce que  le tube soit vide ensuite renvoie 0 qui va arreter le programme
tube plein:: read bloquant */
int main(void)
{
    int i=0;
    int p[2];
    pipe(p);
    while(1){
      char c='x';
      write(p[1],&c,1);
      printf("%d\n",i++);
    }
    return EXIT_SUCCESS;
}
