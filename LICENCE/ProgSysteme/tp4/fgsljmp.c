#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf buf;
void f(){
  longjmp(buf,1);
}
void g(){//ne marche pas après la sortie de la fonction
  setjmp(buf);
}

int main(){
  volatile int i;
  g();
  printf("%d\n",i);
  i++;
  if(i<10){
    f();
  }
  return 0;
}
