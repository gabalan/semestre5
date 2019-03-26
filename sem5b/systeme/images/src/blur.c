
#include "compute.h"
#include "debug.h"
#include "global.h"
#include "graphics.h"
#include "ocl.h"
#include "pthread_barrier.h"

#include <stdbool.h>

///////////////////////////// Version séquentielle simple (seq)

static unsigned pixel_mean (int y, int x)
{
  unsigned r = 0, g = 0, b = 0, a = 0, n = 0;

  int i_d = (y > 0) ? y - 1 : y;
  int i_f = (y < DIM - 1) ? y + 1 : y;
  int j_d = (x > 0) ? x - 1 : x;
  int j_f = (x < DIM - 1) ? x + 1 : x;

  for (int i = i_d; i <= i_f; i++)
    for (int j = j_d; j <= j_f; j++) {
      unsigned c = cur_img (i, j);
      r += (c >> 24) & 255;
      g += (c >> 16) & 255;
      b += (c >> 8) & 255;
      a += c & 255;
      n += 1;
    }

  r /= n;
  g /= n;
  b /= n;
  a /= n;

  return (r << 24) | (g << 16) | (b << 8) | a;
}

// Renvoie le nombre d'itérations effectuées avant stabilisation, ou 0
unsigned blur_compute_seq (unsigned nb_iter)
{
  for (unsigned it = 1; it <= nb_iter; it++) {

    for (int i = 0; i < DIM; i++)
      for (int j = 0; j < DIM; j++)
        next_img (i, j) = pixel_mean (i, j);

    swap_images ();
  }

  return 0;
}


///////////////////////////// Version thread simple


unsigned blur_compute_thread (unsigned nb_iter)
{
  

  return 0;
}
