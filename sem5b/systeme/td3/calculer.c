#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>


typedef double (*funtab_t)(double);
double ajouter_un_dizieme(double d){return d+0.1;}
double ajouter_un_centieme(double d){return d+0.01;}
double ajouter_un_millieme(double d){return d+0.001;}

funtab_t funtab[]={ajouter_un_millieme,ajouter_un_centieme,ajouter_un_dizieme,ajouter_un_millieme};


int nombre_suivant(double *d)
{

}



int main()
{

  return 0;
}
