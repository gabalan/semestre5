#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>


int main(){
  int i;
  jmp_buf buf;
  setjmp(buf);
  printf("%d\n",i);
  i++;
  if(i<10)
    longjmp(buf,1);
  return 0;
}
