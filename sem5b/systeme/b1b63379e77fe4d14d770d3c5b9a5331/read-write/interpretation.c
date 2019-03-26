#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int main(){
printf("hello");
write(2,"world", 5);
return 1;
}
