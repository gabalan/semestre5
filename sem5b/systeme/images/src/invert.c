
#include "compute.h"
#include "debug.h"
#include "global.h"
#include "graphics.h"
#include "ocl.h"
#include "pthread_barrier.h"

#include <pthread.h>
#include <stdbool.h>

static inline unsigned invert_pixel (unsigned c)
{
  return ((unsigned)0xFFFFFFFF - c) | 0xFF;
}


///////////////////////////// Version séquentielle simple (seq)

// Renvoie le nombre d'itérations effectuées avant stabilisation, ou 0
unsigned invert_compute_seq (unsigned nb_iter)
{
  for (unsigned it = 1; it <= nb_iter; it++) {

    for (int i = 0; i < DIM; i++)
      for (int j = 0; j < DIM; j++)
        cur_img (i, j) = invert_pixel (cur_img (i, j));
  }

  return 0;
}


///////////////////////////// Version thread simple
static unsigned nb_threads = 2;
static unsigned _nb_iter;
pthread_barrier_t barrier;

void *thread_starter(void *arg)
{
  size_t me=(size_t)arg;
  int start=(DIM/nb_threads)*me;
  int end=(DIM/nb_threads)*(me+1);
  for (unsigned it = 1; it <= _nb_iter; it++) {

    for (int i = start; i < end; i++)
      for (int j = 0; j < DIM; j++)
        cur_img (i, j) = invert_pixel (cur_img (i, j));
      }

       pthread_barrier_wait(&barrier);

      return NULL;
}

unsigned invert_compute_thread (unsigned nb_iter)
{
  char *str = getenv ("OMP_NUM_THREADS");
  _nb_iter=nb_iter;
  if (str != NULL)
    nb_threads = atoi(str);
  else
    nb_threads = get_nb_cores ();
    pthread_barrier_init(&barrier,NULL,nb_threads);
    pthread_t tids[nb_threads];
   //int ids[nb_threads-1];
  for(int i=0;i<nb_threads;i++){
    //ds[i]=i;
    pthread_create(&tids[i], NULL,thread_starter,(void*)i);
  }

    //  thread_starter((void*)last);
    //void *ret :retourner par pthread_create et qu'on peut passer dans pthread_join comme 2eme arg.
    for(size_t i=0; i<nb_threads; i++){
      pthread_join(tids[i], NULL);
    }
  return 0;
}
