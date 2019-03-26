#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "tp2.h"


// fonction de comparaison (à completer ...) des abscisses de deux
// points A et B: renvoie -1 si "A<B", +1 si "A>B" et 0 sinon
int fcmp_x(point A, point B){
  if(A.x < B.x)
  	return -1;
  else if(A.x > B.x)
  	return 1;
  else 
	return 0;
}


// fonction de comparaison (à completer ...) ordonnées de deux points
// A et B: renvoie -1 si "A<B", +1 si "A>B" et 0 sinon
int fcmp_y(point A,point B){
 if(A.y < B.y)
  	return -1;
 else if(A.y > B.y)
 	 return 1;
 else 
  	return 0;
}

/*La  fonction de comparaison doit renvoyer un entier inférieur, égal, ou
supérieur à zéro si le premier argument  est  respectivement  considéré
comme  inférieur,  égal  ou  supérieur au second. Si la comparaison des
deux arguments renvoie une égalité (valeur de  retour  nulle),  l'ordre
des deux éléments est indéfini.
*/
int comparepoints(point A,point B){
//cas ou A < B
   if(fcmp_x(A,B)==-1 &&  fcmp_y(A,B)==-1)    
	return -1;
//cas ou A > B
   else if(fcmp_x(A,B)==1 &&  fcmp_y(A,B)==1)   
    	return 1;
   else 
	return 0;
}



int comparedistpoints(paire  PA,paire PB){
//cas ou A < B
   if(dist(PA.A,PA.B)<dist(PB.A,PB.B))    
	return -1;
//cas ou A > B
   else if(dist(PA.A,PA.B)>dist(PB.A,PB.B))   
    	return 1;
   else 
	return 0;
}

// algorithme naïf en O(n^2)
// on suppose que P contient au moins n>=2 points
paire algo_naif(point *P, int n){
  paire resultat={{0,0},{0,0}};

//cette boucle double renvoie un tableau trié par ordre croissant 
//selon abcisse et ordonnée
  for(int j=0;j<n;j++){
    for(int i=1;i<n;i++){
  	qsort(&P[0], n, sizeof(double),comparepoints(P[j],P[i]));
       }
    }
//cette boucle double renvoie un tableau trié par ordre croissant 
//selon la distance 
 for(int j=0;j<n;j++){
    for(int i=1;i<n;i++){
  	qsort(&P[0], n, sizeof(double),comparedistpoints({P[j],P[i]},{P[j],P[i+1]}));
       }
    }
  resultat={{P[0]},{P[1]}}  
  return resultat;
	

}

// algorithme récursif en O(nlogn)
// on suppose que P contient au moins n>=2 points
paire algo_rec(point *P, int n){
  paire resultat={{0,0},{0,0}};
  
 //construction de PX , PY
  double *PX;
  double *PY;
  for(int i=0;i<n;i++){
	PX=P[i].x;
	PY=P[i].y;
}

if(n==2||n==3)
   return algo_rec(PX,n);

//renvoyer PPPPrec(PX,PY)

// construction des tableaux Ax,Bx,Ay etBy à partir de x,Px et Py.
	double *Ax,*Ay;
	double *Bx,By;

return resultat;


}


int main(int argc, char *argv[]){
  
  srandom(time(NULL));

  if(argc==2){
    //
    // partie à ne pas modifier
    //
    if(!isdigit(argv[1][0])){ printf("Forgot \"naif\" or \"rec\"?.\n"); exit(1); }
    int n=atoi(argv[1]);
    point *P=point_random(n);
    if((P==NULL)||(n<1)){ printf("Empty point set.\n"); exit(1); }
    printf("%i\n",n);
    for(int i=0;i<n;i++)
      printf(FORM" "FORM"\n",P[i].x,P[i].y);
    return 0;
  }
    
  if(argc==3){
    //
    // partie à ne pas modifier
    //
    int n;
    paire res={{-1,0},{0,0}};
    point *P=read(argv[1],&n);
    if(!strcmp(argv[2],"naif")) res=algo_naif(P,n);
    if(!strcmp(argv[2],"rec")) res=algo_rec(P,n);
    if(res.A.x<0){ printf("Unknown algorithm.\n"); exit(1); }
    printf("point A: "FORM" "FORM"\n",res.A.x,res.A.y);
    printf("point B: "FORM" "FORM"\n",res.B.x,res.B.y);
    printf("distance: "FORM"\n",dist(res.A,res.B));
    return 0;
  }

  // pour vos tests personnels, si nécessaire, modifier le main()
  // seulement ci-dessous
  
  ;;;;
  ;;;;
  ;;;;
  
  return 0;
}
