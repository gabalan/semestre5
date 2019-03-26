#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
int affichergrille (game jeu){
//AFFICHER LA GRILLE
//affiche le nombre de chaque type de monstre
printf("  Z:%d V:%d G:%d S:%d   \n",required_nb_monsters(jeu, ZOMBIE),required_nb_monsters(jeu, VAMPIRE),required_nb_monsters(jeu, GHOST),required_nb_monsters(jeu, SPIRIT));
printf("\n");
//afficher le nombre de monstre visibles de chaque coté(N,S,E,O)

//cote NORD
printf("      ");
for(int i=0;i<game_width(jeu);i++){
  printf("%d ",required_nb_seen(jeu, N, i));
}
printf("      \n");
printf("\n");

//affichage du contenu de chaque case de notre grille ET les cotes EST OUEST
int h=game_height(jeu)-1;
int w =game_width(jeu);
  for(int y=h;y>=0;y--){
//for(int v=3; v>=0; v--){
    printf("|  %d  ",required_nb_seen(jeu, W, h));
  for(int x=0;x<w;x++){
   //for(int k=0;k<4;k++){
   content contenu=get_content(jeu,x,y);
    switch (contenu) {
      case  MIRROR:
       printf("/ ");
       break;
      case  ANTIMIRROR:
        printf("\\ ");
        break;
      case  VMIRROR:
         printf(": ");
         break;
      case  HMIRROR:
          printf("- ");
          break;
      case  VAMPIRE:
           printf("V ");
           break;
      case  GHOST:
            printf("G ");
            break;
      case  ZOMBIE:
             printf("Z ");
             break;
      case  SPIRIT:
              printf("S ");
              break;
      case EMPTY:
      printf("  ");
      break;
    }

    }
    printf("  %d  |\n",required_nb_seen(jeu, E, h));
    h--;
}


printf("\n");
printf("       ");
for(int i=0;i<game_width(jeu);i++){
  printf("%d ",required_nb_seen(jeu, S, i));
}
printf("      \n");
printf("\n");

return EXIT_SUCCESS;
}
game  grille(int width,int height ){
  game jeu=new_game_ext(width,height);
  int h=game_height(jeu);
  int w=game_width(jeu);
  //ajout des mirrors
  for(int i=h-1;i>=0;i--){
    for(int j=0;j<w;j++){
      if(i%2==1 && j==0){
        add_mirror_ext(jeu,ANTIMIRROR,i,j);
      }
      else if((i==2 || i==3) && j==2 ){
        add_mirror_ext(jeu,MIRROR,i,j);
      }

    }
  }
  //les nombres des monstres
  int nb_monsters=compt_case_vide(jeu);
  set_required_nb_monsters(jeu, ZOMBIE, nb_monsters/2);
  set_required_nb_monsters(jeu, VAMPIRE, nb_monsters*(1/4));
  set_required_nb_monsters(jeu, GHOST, nb_monsters/4);
  set_required_nb_monsters(jeu, ZOMBIE, 0);
  //les cotés
  for(int i=0;i<2;i++){
    for(int j=0;j<w;j++){
      set_required_nb_seen(jeu, i,j, i+j);
    }
  }
  for(int i=2;i<4;i++){
    for(int j=0;j<w;j++){
      set_required_nb_seen(jeu, i,j, i+j);
    }
  }
return jeu;
}

int compt_case_vide(game g){
  int h=game_height(g);
  int w=game_width(g);
  int compt=0;
  for(int i=h-1;i>=0;i--){
    for(int j=0;j<w;j++){
      if(get_content(g,i,j)==EMPTY){
        compt=compt+1;
      }
    }
  }
  return compt;
}
int main(){
  game jeu=grille(4,4);
  affichergrille(jeu);
  return EXIT_SUCCESS;
}
