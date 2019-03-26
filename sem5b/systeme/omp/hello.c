#include <stdio.h>
#include <omp.h>
int main()
{
   #pragma omp parallel
   printf("Bonjour %d !\n",omp_get_thread_num() );
   printf("Au revoir !\n");

  return 0;
}
