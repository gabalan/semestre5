#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *HelloGoodbye(void *p)
{
  int id=*(int*)p;

  printf("%d: bonjour\n",id);
  sleep(1);
  printf("%d: a bientot\n",id);

  return NULL;
}
int
main(int argc, char *argv[])
{
  if (argc<2){
    fprintf(stderr, "argument insuffusant\n" );
    exit(EXIT_FAILURE);
  }
  int entier=atoi(argv[1]);
  pthread_t tab[entier];
  int ids[entier];
  for(int i=0;i<entier;i++){
    ids[i]=i;
    pthread_create(&tab[i], NULL, HelloGoodbye,&ids[i]);
  }
    //void *ret :retourner par pthread_create et qu'on peut passer dans pthread_join comme 2eme arg.
    for(int i=0; i<entier; i++){
      pthread_join(tab[i], NULL);
    }
  return EXIT_SUCCESS;
}
