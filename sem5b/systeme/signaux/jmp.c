
#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <setjmp.h>
jmp_buf env;
void f();
int main(){
volatile int i=0 ;
setjmp(env);
printf("%d\n",i);
i++;
if (i<10) f();
return 0;
}
/*
mov i,%eax
add $1 ,%eax
mov %eax,1
*/

void f(){
  longjmp(env,1);

}

void g(){

}
