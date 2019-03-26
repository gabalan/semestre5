#include "game.h"
#include "game_io.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>


#define MAX 4096//on suppose que le maximum de ligne à lire  ne depasse pas 406
/*pour faire la fonction load_game on va utiliser deux fonctions auxiliaire :la premiere qui la read_next_line
qui nous permet de lire une ligne en entier et stock les caracteres separé par  des espaces  dans un tableau de caractere et la seconde
c'est une fonction qui est convert_line qui en cas de besoin de  convertir la lgne stocker dans le resultat de
read_next_line  en  long on l'utilse .En gros ,read_next_line lit la ligne depuis le fichier et convert_line la convertit
si c'est necessaire */

char* read_next_line(FILE* p_f, long* p_size){
  char* s = malloc(MAX*sizeof(char));
  if(s==NULL){
    fprintf(stderr,"error");
    free(s);
    return NULL;
 }
 long old_pos = ftell(p_f);
 long len = 0;
 if(fgets(s,MAX, p_f ) != NULL){
   len = ftell(p_f)-old_pos;
   if(s[len-1]=='\n'){
     s[len-1]= '\0';
     len--;
 } else{
   if(!feof(p_f)){      // to detect error from last line without '\n'
    fprintf(stderr, "line too long ...");
    exit(EXIT_FAILURE);
  }
}
(*p_size)=len;
return s;
}
free(s);
return NULL; // in case of eof
}
long* convert_line(char* line, long* p_size){
  long* arr = malloc((*p_size)*sizeof(long));
  if(arr ==NULL){
    fprintf(stderr,"error");
    free(arr);
    return NULL;
  }
  long arr_s= 0;
  char* token = strtok(line," ");
  while(token !=NULL){
    char* end_value = token;
    long value = strtol(token, &end_value,10);
    if ((*end_value)=='\0') {   // convert was successfull
      arr[arr_s]=value;
      arr_s++;
    }else{
      free(arr);
      return NULL;
    }
    token = strtok(NULL," ");
  }
  (*p_size)=arr_s;
  return arr;
}

game load_game(char* filename){
  FILE* fichier =fopen(filename,"r");
  if(fichier == NULL){
    fprintf(stderr,"invalide fichier sur load_game");
    exit(EXIT_FAILURE);
  }
//  char* end=NULL;
  long* tab=NULL;

  int compt = 1;                   // pour connaitre le nombre de ligne à lire
  long size = 0;
  char* line =NULL;
  line =read_next_line(fichier, &size);
  tab = convert_line(line, &size);
  if(!tab){
    fprintf(stderr, "tableaux vide");
    exit(EXIT_FAILURE);
  }
  if(size == 0 || size>2){

    fprintf(stderr,"error de size en 83");
    exit(EXIT_FAILURE);
  }

    game jeu = new_game_ext(tab[0],tab[1]);
  line =read_next_line(fichier, &size);
  while(compt < 6 && line !=NULL){
    if(!line){
      fprintf(stderr, "echec");
      exit(EXIT_FAILURE);
    }
    tab = convert_line(line, &size);
    if(tab == NULL){
      fprintf(stderr,"tab invalide dans case2");
      exit(EXIT_FAILURE);
    }

    switch (compt) {

    case 1: {
      for(int i = 0; i < size; i++){
        if(i == 0){
          set_required_nb_monsters(jeu, VAMPIRE, tab[i]);
        }
        if( i ==1){
          set_required_nb_monsters(jeu, GHOST, tab[i]);
        }
        if(i == 2){
            set_required_nb_monsters(jeu, ZOMBIE, tab[i]);
        }else{
          set_required_nb_monsters(jeu, SPIRIT, tab[i]);
        }
      }
    }
    break;
    case 2: {                                                // troisième ligne du fichier

      for(int i = 0; i < size; i++){
        set_required_nb_seen(jeu, N ,i , tab[i]);
      }
    }
    break;
    case 3: {                                              // quatrième ligne du fichier
      for(int i = 0; i < size; i++){
        set_required_nb_seen(jeu, S ,i , tab[i]);
      }
    }
    break;
    case 4: {                                            // cinquième ligne du fichier
      for(int i = 0; i < size; i++){
        set_required_nb_seen(jeu, E ,i , tab[i]);
      }
    }
    break;
    case 5: {                                           // sixieme ligne du fichier
      for(int i = 0; i < size; i++){
        set_required_nb_seen(jeu, W ,i , tab[i]);
      }
    }
    break;
    }
    line = read_next_line(fichier, &size);
    compt = compt + 1;
  }
  int compt2 = game_height(jeu)-1;

  while(compt2 >= 0  && line != NULL){
    if(!line){
      fprintf(stderr, "echec");
      exit(EXIT_FAILURE);
    }
    for(int i = 0; i < strlen(line); i=i+2){
      if(!line[i]){
        fprintf(stderr,"invalide char");
        exit(EXIT_FAILURE);
      }
      switch (line[i]) {
        case '\\':{
          add_mirror_ext(jeu, ANTIMIRROR, i/2, compt2);
        }
        break;
        case '/' :{
          add_mirror_ext(jeu, MIRROR, i/2, compt2);
        }
        break;
        case '.' :{
          add_mirror_ext(jeu, EMPTY, i/2, compt2);
        }
        break;
        case '|' : {
          add_mirror_ext(jeu, VMIRROR, i/2, compt2);
        }
        break;
        case '-': {
          add_mirror_ext(jeu, HMIRROR, i/2, compt2);
        }
        break;
        default  :
        exit(EXIT_FAILURE);
      }

    }
    line = read_next_line(fichier,&size);

    compt2--;
  }

fclose(fichier);
return jeu;

}

void save_game(cgame g, char* filename){
    if(g==NULL || filename==NULL){
        fprintf(stderr,"les pointeurs sont invalides");//on teste les pointeurs passés en parametre
        exit(EXIT_FAILURE);
    }
    FILE* fichier=fopen(filename,"w");//ouverture du fichier filename(où on doit les donnés de notre jeux) en mode ecriture
    if(fichier==NULL){
      fprintf(stderr,"echec de l'ouverture du fichier");//test si l'ouverure a échoué si oui on sort sinon on continue
      exit(EXIT_FAILURE);
    }
    /* A partir de là que le fichier est ouvert on commence à ecrire les solutions dans le fichier mais à condition
    aussi que le jeu soit fini c'est à dire game_is_over*/
    // le "fprintf(fichier,"\n")" signifie juste quedans le ficher il faut retour à la ligne


        fprintf(fichier,"%d %d", game_width(g), game_height(g));//la premieree ligne du fichier correspond à la largeur et la hauteur de notre grille
        fprintf(fichier,"\n");
        //la 2eme au nombre de chaque type de monstre
        fprintf(fichier,"%d %d %d %d ",required_nb_monsters(g, VAMPIRE),required_nb_monsters(g, GHOST),required_nb_monsters(g, ZOMBIE),required_nb_monsters(g,SPIRIT));
        fprintf(fichier,"\n");
        // le nombre  de monstre visible coté nord à chaque position de la largeur
        for(int i=0;i<game_width(g);i++){
          fprintf(fichier,"%d ",required_nb_seen(g, N, i));
        }
        fprintf(fichier,"\n");
        // le nombre  de monstre visible coté sud à chaque position de la largeur
        for(int i=0;i<game_width(g);i++){
          fprintf(fichier,"%d ",required_nb_seen(g, S, i));
        }
        fprintf(fichier,"\n");
        // le nombre  de monstre visible coté EST à chaque position de la hauteur
        for(int i=0;i<game_height(g);i++){
          fprintf(fichier,"%d ",required_nb_seen(g, E, i));
        }
        fprintf(fichier,"\n");
        // le nombre  de monstre visible coté OUEST à chaque position de la hauteur
        for(int i=0;i<game_height(g);i++){
          fprintf(fichier,"%d ",required_nb_seen(g, W, i));
        }
        fprintf(fichier,"\n");
        //on parcours notre grille on recupere le contenu de chaque case et on l'ecrit directement dans le fichier
        for(int j=game_height(g)-1;j>=0;j--){
          for(int i=0;i<game_width(g);i++){
            content contenue=get_content(g,i,j);
            switch (contenue) {
              case VAMPIRE:
              fprintf(fichier,"V ");
              break;
              case ZOMBIE:
              fprintf(fichier,"Z ");
              break;
              case GHOST:
              fprintf(fichier,"G ");
              break;
              case SPIRIT:
              fprintf(fichier,"S ");
              break;
              case MIRROR:
              fprintf(fichier,"/ ");
              break;
              case ANTIMIRROR:
              fprintf(fichier,"\\ ");
              break;
              case VMIRROR:
              fprintf(fichier,"| ");
              break;
              case HMIRROR:
              fprintf(fichier,"- ");
              break;
              case EMPTY:
              fprintf(fichier," ");
            }
          }
          fprintf(fichier,"\n");

    }
    fclose(fichier);//ferme le fichier

}
