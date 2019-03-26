#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(){
 char c;
  int n;
  
 do{
   n=fread(&c,1,1,stdin);
	if(n<1)
	  break;
	n=fwrite(&c,1,1,stdout);
	}while (n==1);
    
  return EXIT_SUCCESS;
  	
   

}
