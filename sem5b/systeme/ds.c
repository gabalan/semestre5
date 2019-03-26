#include <stdio.h>
#include<stdlib.h>
main(){
  printf("S1");
  fprintf(stderr,"E1");
  printf("S2\n");
  fprintf(stderr,"E2");
  printf("S3");
  *((int*)NULL)=42;
}
