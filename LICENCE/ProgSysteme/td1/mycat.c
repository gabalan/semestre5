#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(){
  char c;
  int n;
  
  do{
    n=read(STDIN_FILENO,&c,1);
	if(n<1)
	  break;
	n=write(STDOUT_FILENO,&c,1);
	}while (n==1);
    

/*while(read(0,&c,1)>0)
	write(1,&c,&);
  */
return EXIT_SUCCESS;
  
}
