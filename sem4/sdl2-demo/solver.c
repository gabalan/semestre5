#include"game.h"
#include<stdlib.h>
#include<stdio.h>
#include"game_io.h"

int affichergrille (game jeu){
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
           printf("| ");
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

  void afficherMonstre(content monstre){
    switch (monstre) {
      case  MIRROR:
       printf("/ ");
       break;
      case  ANTIMIRROR:
        printf("\\ ");
        break;
      case  VMIRROR:
         printf("| ");
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
       default:
      printf(" . ");
      break;

    }
  }

  bool is_game_possible(game g){
    if ( current_nb_monsters(g,ZOMBIE) > required_nb_monsters(g,ZOMBIE)){			//verifie que le nombre de zombie requis est egal au nombre de zombie dans la grille
      return false;									//sinon la fonction renvoie false
    }
    if ( current_nb_monsters(g,GHOST) > required_nb_monsters(g,GHOST)){			//verifie que le nombre de ghost requis est egal au nombre de ghost dans la grille
      return false;									//sinon la fonction renvoie false
    }
    if ( current_nb_monsters(g,VAMPIRE) > required_nb_monsters(g,VAMPIRE)){		//verifie que le nombre de vampire requis est egal au nombre de vampire dans la grille
      return false;									//sinon la fonction renvoie false
    }
    if ( current_nb_monsters(g,SPIRIT) > required_nb_monsters(g,SPIRIT)){			//verifie que le nombre de vampire requis est egal au nombre de vampire dans la grille
      return false;									//sinon la fonction renvoie false
    }
    for(int u = 0; u < game_width(g); u++){				//boucle sur le nombre de lignes
      //verifie que le nombre de monstre que l'on doit voir à chaque position et bien egal au nombre de monstre que l'on voit
          if (required_nb_seen(g , N , u) < current_nb_seen(g , N , u)){
              return false;
          }
    }
    for(int u = 0; u < game_width(g); u++){				//boucle sur le nombre de lignes
      //verifie que le nombre de monstre que l'on doit voir à chaque position et bien egal au nombre de monstre que l'on voit
          if (required_nb_seen(g , S , u) < current_nb_seen(g , S , u)){
              return false;
          }
    }
    for(int u = 0; u < game_height(g); u++){				//boucle sur le nombre de lignes
      //verifie que le nombre de monstre que l'on doit voir à chaque position et bien egal au nombre de monstre que l'on voit
          if (required_nb_seen(g , E , u) < current_nb_seen(g , E , u)){
              return false;
          }
    }
    for(int u = 0; u < game_height(g); u++){				//boucle sur le nombre de lignes
      //verifie que le nombre de monstre que l'on doit voir à chaque position et bien egal au nombre de monstre que l'on voit
          if (required_nb_seen(g , W , u) < current_nb_seen(g , W , u)){
              return false;
          }
    }
    // for(int i = 0; i < game_height(g) ; i++){								//boucle sur les directions {N,S,E,W}
    //   if(i == 0 || i == 1){								//si les direction sont nord et sud alors nous prenons au max le nombre de lignes
    //     for(int u = 0; u < game_width(g); u++){				//boucle sur le nombre de lignes
    //       //verifie que le nombre de monstre que l'on doit voir à chaque position et bien egal au nombre de monstre que l'on voit
    //           if (required_nb_seen(g , i , u) < current_nb_seen(g , i , u)){
    //               return false;
    //           }
    //     }
    //   }
    //   else{										//si les direction sont est et ouest alors nous prenons au max le nombre de colonnes
    //     for(int u = 0; u < game_height(g); u++){				//boucle sur le nombre de colonnes
    //     //verifie que le nombre de monstre que l'on doit voir à chaque position et bien egal au nombre de monstre que l'on voit
    //           if (required_nb_seen(g , i , u) < current_nb_seen(g , i , u)){
    //               return false;
    //           }
    //     }
    //   }
    // }
    return true;	// si il n'est rentrée dans aucune des conditions c'est que le jeu est finie donc renvoie true
  }


bool sol_recursive(game jeu, int position, bool retour){

  if (jeu == NULL){
   exit(EXIT_FAILURE);
  }
  if (position < 0){
    return false;
  }
  if (position == game_width(jeu)*game_height(jeu)){
    if(is_game_over(jeu) == true){
      affichergrille(jeu);
      return true;
    }
    return false;
  }
  int x = position%game_width(jeu);
  int y = position/game_height(jeu);
  // printf("la position courante est : %d\n",position);
  // printf("la largeur est : %d\n",x);
  // printf("la hauteur est : %d\n",y);
  // printf("le contenu de la position courante est :");
  // afficherMonstre(get_content(jeu,x,y));
  // printf("\n");
  content c=get_content(jeu,x,y);
  if( c== MIRROR || c == HMIRROR || c == VMIRROR || c == ANTIMIRROR ){
    //affichergrille(jeu);
    if(retour==true){
      return sol_recursive(jeu,position - 1,true);
    }else{
      return sol_recursive(jeu, position + 1,false);
    }

  }
  if (get_content(jeu,x,y)== EMPTY){
    add_monster(jeu,VAMPIRE,x,y);
    //affichergrille(jeu);
    if(is_game_possible(jeu)){
      //affichergrille(jeu);
      return sol_recursive(jeu,position + 1,false);
    }
    else{
      //affichergrille(jeu);
      return sol_recursive(jeu,position,false);

    }
  }
  else if (get_content(jeu,x,y)== VAMPIRE){
    add_monster(jeu,GHOST,x,y);
    if (is_game_possible(jeu)){
      //affichergrille(jeu);
      return sol_recursive(jeu,position + 1,false);
    }else{
      //affichergrille(jeu);
      return sol_recursive(jeu,position,false);
    }
  }
  else if (get_content(jeu,x,y)== GHOST){
    //printf("fantom");
    add_monster(jeu,ZOMBIE,x,y);
    if (is_game_possible(jeu)){
      //affichergrille(jeu);
      return sol_recursive(jeu,position + 1,false);
    }else{
      //affichergrille(jeu);
      return sol_recursive(jeu,position,false);
    }
  }
  else if (get_content(jeu,x,y)== ZOMBIE){
    add_monster(jeu,SPIRIT,x,y);
    if (is_game_possible(jeu)){
      //affichergrille(jeu);
      return sol_recursive(jeu,position + 1,false);
    }else{
      //affichergrille(jeu);
      return sol_recursive(jeu,position,false);
    }
  }
  else{
    add_monster(jeu,EMPTY,x,y);
    return sol_recursive(jeu,position - 1,true);
  }
}
bool s=false;
void FIND_ALL(game jeu){
  int compt=0;

  int size = game_width(jeu) * game_height(jeu) -1;
  //bool t=false;
    s=sol_recursive(jeu,0,false);
    while(s){

        s=sol_recursive(jeu,size,true);
        printf("%d",size);
          affichergrille(jeu);
        }
      }
      //printf("%d",compt);

  //affichergrille(jeu);











int main(int argc,char *argv[]){
  if(argc !=4){
    fprintf(stderr,"manque d'arguments");
    exit(EXIT_FAILURE);
  }
  if(strcmp(argv[1],"FIND_ONE") != 0 && strcmp(argv[1],"NB_SOL") != 0 && strcmp(argv[1],"FIND_ALL") != 0){
    exit(EXIT_FAILURE);
  }
  game jeu = load_game(argv[2]);
  if(strcmp(argv[1],"FIND_ONE")==0){
    bool t=sol_recursive(jeu,0,false);
    save_game(jeu,argv[3]);
  }
  if(strcmp(argv[1],"FIND_ALL")==0){
    FIND_ALL(jeu);
  }
  return EXIT_SUCCESS;
}
