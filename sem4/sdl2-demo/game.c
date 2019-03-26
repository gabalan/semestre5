#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"

#define HEIGHT 4
#define WIDTH 4

struct game_s{
  int required_nb_ghosts;
  int required_nb_vampires;
  int required_nb_zombies;
  int required_nb_spirits;
  int height;
  int width;
  int ** required_nb_seen;
  content * board;
};


/**
* @brief creates an empty game with all squares set to empty, all labels and the number of required monsters set to 0.
* @return the created game
**/
game new_game(){
  game g = (game) calloc(1,sizeof(struct game_s));
  if(g==NULL){
    fprintf(stderr,"not enough memory\n");
    exit(EXIT_FAILURE);
  }
  g->board = (content*)calloc(HEIGHT*WIDTH, sizeof(content));
  if (g->board==NULL){
    fprintf(stderr,"not enough memory\n");
    free(g);
    exit(EXIT_FAILURE);
  }
  g->required_nb_seen=(int**) calloc(NB_DIR,sizeof(int*));
  if(g->required_nb_seen==NULL){
    fprintf(stderr,"not enough memory\n");
    free(g->board);
    free(g);
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < NB_DIR; i++){
    if(i<2){
      g->required_nb_seen[i] = (int*)calloc(WIDTH,sizeof(int));
    }
    else{
      g->required_nb_seen[i] = (int*)calloc(HEIGHT,sizeof(int));
    }
    if(g->required_nb_seen[i]==NULL){
      fprintf(stderr,"not enough memory\n");
      if(i>=1){
        for(int j=i;j>=0;j--){
          free(g->required_nb_seen[j]);
        }
      }
      free(g->required_nb_seen);
      free(g->board);
      free(g);
      exit(EXIT_FAILURE);
    }
  }
  g->width = WIDTH;
  g->height = HEIGHT;
  return g;
}

/**
* @brief creates an empty game with all labels set to 0.
* @param width number of columns of the board
* @param height number of lines of the board
* @return the created game
**/

game new_game_ext(int width, int height){
  game g = (game) calloc(1,sizeof(struct game_s));
  if(g==NULL){
    fprintf(stderr,"not enough memory\n");
    exit(EXIT_FAILURE);
  }
  g->board = (content*)calloc(height*width, sizeof(content));
  if (g->board==NULL){
    fprintf(stderr,"not enough memory\n");
    free(g);
    exit(EXIT_FAILURE);
  }
  g->required_nb_seen=(int**) calloc(NB_DIR,sizeof(int*));
  if(g->required_nb_seen==NULL){
    fprintf(stderr,"not enough memory\n");
    free(g->board);
    free(g);
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < NB_DIR; i++){
    if(i<2){
      g->required_nb_seen[i] = (int*)calloc(width,sizeof(int));
    }
    else{
      g->required_nb_seen[i] = (int*)calloc(height,sizeof(int));
    }
    if(g->required_nb_seen[i]==NULL){
      fprintf(stderr,"not enough memory\n");
      if(i>=1){
        for(int j=i-1;j>=0;j--){
          free(g->required_nb_seen[j]);
        }
      }
      free(g->required_nb_seen);
      free(g->board);
      free(g);
      exit(EXIT_FAILURE);
    }
  }
  g->width = width;
  g->height = height;
  return g;
}


/**
* @brief creates a game from a board.
* It uses a given board possibly with its mirrors, and a list of labels.
* It checks that the proposed dimensions (that should match the list)
* match the size of the board.
*
* @param width number of columns of the board
* @param height number of lines of the board
* @param labels an array of four pointers towards array of labels (namely, labels[N], labels[S], labels[E], labels[W]).
* The labels are given according to increasing coordinate value (from S to N or from W to E)
* @param board an array of all the board squares, stored line-by-line (possibly with mirrors set already)
* @param required_nb_ghosts the number of ghosts required in the game.
* @param required_nb_vampires the number of vampires required in the game.
* @param required_nb_zombies the number of zombies required in the game.
* @param required_nb_spirits the number of spirits required in the game.
* @return the created game
**/

game setup_new_game_ext(int width, int height, int *labels[NB_DIR], content * board,
  int required_nb_ghosts,  int required_nb_vampires,
  int required_nb_zombies, int required_nb_spirits){

    game g = new_game_ext(width, height);
    if(g == NULL || g->board == NULL || board == NULL || g->required_nb_seen == NULL){
      fprintf(stderr, "Error not enough memory");
      exit(EXIT_FAILURE);
    }
    for(unsigned int i=0;i<width*height;i++)
    g->board[i] = board[i];
    g->required_nb_ghosts = required_nb_ghosts;
    g->required_nb_vampires = required_nb_vampires;
    g->required_nb_zombies = required_nb_zombies;
    g->required_nb_spirits = required_nb_spirits;
    g->height = height;
    g->width = width;
    for(unsigned int i=0;i<NB_DIR;i++){
      if (i<2){
        for(int j=0;j<width;j++){
          if(labels[i][j]<0){
            fprintf(stderr,"value put at labels[%d][%d] must be positive (actual value : %d)\n",i,j,labels[i][j]);
            delete_game(g);
            exit(EXIT_FAILURE);
          }
          g->required_nb_seen[i][j] = labels[i][j];
        }
      }
      else{
        for(int j=0;j<height;j++){
          if(labels[i][j]<0){
            fprintf(stderr,"value put at labels[%d][%d] must be positive (actual value : %d)\n",i,j,labels[i][j]);
            delete_game(g);
            exit(EXIT_FAILURE);
          }
          g->required_nb_seen[i][j] = labels[i][j];
        }
      }
    }
    return g;
  }



  /**
  * @brief return the number of lines on the game
  *
  * @param game the game.
  * @return the height of the game
  **/

  int game_height(cgame game){
    if (game == NULL){
      fprintf(stderr, "Null pointer!\n");
      exit(EXIT_FAILURE);
    }
    return game->height;
  }



  /**
  * @brief return the number of columns on the game
  *
  * @param game the game.
  * @return the width of the game
  */

  int game_width(cgame game){
    if (game == NULL){
      fprintf(stderr, "Null pointer!\n");
      exit(EXIT_FAILURE);
    }
    return game->width;
  }

  /**
  * @brief creates a game from a board description.
  * It uses a given board possibly with its mirrors, and a list of labels.
  * @param labels an array of four pointers towards array of labels (namely, labels[N], labels[S], labels[E], labels[W]).
  * The labels are given according to increasing coordinate value (from S to N or from W to E)
  * @param board an array of all the board squares, stored sequentially line by line starting from coordinate (0,0)
  * @param required_nb_ghosts the number of ghosts required in the game.
  * @param required_nb_vampires the number of vampires required in the game.
  * @param required_nb_zombies the number of zombies required in the game.
  * @return the created game
  **/

  game setup_new_game(int *labels[NB_DIR], content * board, int required_nb_ghosts,  int required_nb_vampires, int required_nb_zombies){
    game g = new_game();
    if(g == NULL || g->board == NULL || board == NULL || g->required_nb_seen == NULL){
      fprintf(stderr, "Error not enough memory");
      exit(EXIT_FAILURE);
    }
    for(unsigned int i=0;i<WIDTH*HEIGHT;i++)
    g->board[i] = board[i];
    g->required_nb_ghosts = required_nb_ghosts;
    g->required_nb_vampires = required_nb_vampires;
    g->required_nb_zombies = required_nb_zombies;
    g->height = HEIGHT;
    g->width = WIDTH;
    for(unsigned int i=0;i<NB_DIR;i++){
      if (i<2){
        for(int j=0;j<WIDTH;j++){
          if(labels[i][j]<0){
            fprintf(stderr,"value put at labels[%d][%d] must be positive (actual value : %d)\n",i,j,labels[i][j]);
            delete_game(g);
            exit(EXIT_FAILURE);
          }
          g->required_nb_seen[i][j] = labels[i][j];
        }
      }
      else{
        for(int j=0;j<WIDTH;j++){
          if(labels[i][j]<0){
            fprintf(stderr,"value put at labels[%d][%d] must be positive (actual value : %d)\n",i,j,labels[i][j]);
            delete_game(g);
            exit(EXIT_FAILURE);
          }
          g->required_nb_seen[i][j] = labels[i][j];
        }
      }
    }
    return g;
  }

  /**
  * @brief adds a mirror on the game board
  * @param game the game board where to add the mirror
  * @param dir the direction on which to add the mirror: 0 for +45 degrees (/), 1 for -45 degrees (\\)
  * @param col which column to insert the mirror on (0<=col<4)
  * @param line which line to insert the mirror on (0<=line<4)
  **/

  void add_mirror(game game, int dir, int col, int line){
    if (game==NULL){
      fprintf(stderr, "Invalid game pointer sent to add_mirror!\n");
      exit(EXIT_FAILURE);
    }
    if (col>=game_width(game) ||col<0){
      fprintf(stderr, "Invalid integer col sent to add_mirror!\n");
      exit(EXIT_FAILURE);
    }
    if (line>=game_height(game) || line<0){
      fprintf(stderr, "Invalid integer line sent to add_mirror!\n");
      exit(EXIT_FAILURE);
    }
    if (dir==0){
      game->board[game_width(game)*line+col]=MIRROR;
    }
    if (dir==1){
      game->board[game_width(game)*line+col]=ANTIMIRROR;
    }
  }

  /**
  * @brief adds a mirror on the game board
  * @param game the game board where to add the mirror
  * @param mirror_type a content that corresponds to a mirror (MIRROR, ANTI_MIRROR, VMIRROR or HMIRROR)
  * @param col which column to insert the mirror on. (0<=col<width)
  * @param line which line to insert the mirror on (0<=line<height)
  **/

  void add_mirror_ext(game game, content mirror_type, int col, int line){
    if (game==NULL){
      fprintf(stderr, "Invalid game pointer sent to add_mirror_ext!\n");
      exit(EXIT_FAILURE);
    }
    if (col>=game_width(game) ||col<0){
      fprintf(stderr, "Invalid integer col sent to add_mirror_ext!\n");
      exit(EXIT_FAILURE);
    }
    if (line>=game_height(game) || line<0){
      fprintf(stderr, "Invalid integer line sent to add_mirror_ext!\n");
      exit(EXIT_FAILURE);
    }
    game->board[game_width(game)*line+col] = mirror_type;
  }

  /**
  * @brief sets the label of a game
  * @param game the game to modify
  * @param side the side of the game where the label should be modified
  * @param pos the position that the label should be modified (from S to N or from W to E)
  * @param value the new value to give to the label
  **/

  void set_required_nb_seen(game game, direction side, int pos, int value){
    if(game ==NULL){
      fprintf(stderr, "Game does not exist\n");
      exit(EXIT_FAILURE);
    }
    if(side == E || side == W){
      if(pos>game_height(game) || pos<0){
        fprintf(stderr,"Can't be called out of bound\n");
        exit(EXIT_FAILURE);
      }
    }
    if(side == N || side == S){
      if(pos>game_width(game) || pos<0){
        fprintf(stderr,"Can't be called out of bound\n");
        exit(EXIT_FAILURE);
      }
    }
    if(value < 0){
      fprintf(stderr,"value must be positive\n");
      exit(EXIT_FAILURE);
    }
    game->required_nb_seen[side][pos]=value;
  }



  /**
  * @brief modifies the aimed number of a given monster on the board
  * @param game the game that you want to modify the information about
  * @param monster the type of monster (should be GHOST, VAMPIRE, ZOMBIE or SPIRIT)
  * @param value the value you want to set to the parameter.
  **/

  void set_required_nb_monsters(game game, content monster, int value){
    if (game==NULL){
      fprintf(stderr, "game does not exist\n");
      exit(EXIT_FAILURE);
    }
    if (monster != ZOMBIE && monster !=VAMPIRE && monster!=GHOST && monster!=SPIRIT){
      fprintf(stderr,"can't be called over something that is not a monster (nothing will happen)");
    }
    if(monster == ZOMBIE){
      game->required_nb_zombies=value;
    }
    if(monster == VAMPIRE){
      game->required_nb_vampires=value;
    }
    if(monster == GHOST){
      game->required_nb_ghosts=value;
    }
    if(monster == SPIRIT){
      game->required_nb_spirits=value;
    }
  }

  /**
  * @brief Clone the game g_src
  * @param g_src the game to clone
  * @return the clone of g_src
  **/
  game copy_game (cgame g_src){
    if (g_src==NULL) {
      exit(EXIT_FAILURE);
    }
    game g= new_game_ext(g_src->width,g_src->height);
    g->required_nb_zombies= g_src->required_nb_zombies;
    g->required_nb_ghosts= g_src->required_nb_ghosts;
    g->required_nb_vampires=g_src->required_nb_vampires;
    g->required_nb_spirits=g_src->required_nb_spirits;
    g->height=game_height(g_src);
    g->width=game_width(g_src);
    for (int i=0; i<g->width*g->height; i++){
      g->board[i] = g_src->board[i];
    }
    for (int i=0; i<NB_DIR; i++){
      if (i<2){
        for (int j=0;j<game_height(g); j++)
        g->required_nb_seen[i][j]=g_src->required_nb_seen[i][j];
      }
      else{
        for (int j=0;j<game_height(g); j++)
        g->required_nb_seen[i][j]=g_src->required_nb_seen[i][j];
      }
    }
    return g;
  }


  /**
  * @brief Destroy the game and free allocated memory
  * @param g the game to destroy
  **/

  void delete_game (game g){
    if(g != NULL){
      if (g->required_nb_seen != NULL) {
        for(int i = 0; i < NB_DIR; i++){
          if (g->required_nb_seen[i] != NULL) free(g->required_nb_seen[i]);
        }
        free(g->required_nb_seen);
      }
      if (g->board != NULL) free(g->board);
      free(g);
    }
  }

  /**
  * @brief return the label on the side of the board
  * @param game the game we consider
  * @param side the side of the board we want the label from
  * @param pos the position of the label you want (from S to N or from W to E)
  **/

  int required_nb_seen(cgame game, direction side, int pos){
    if (game == NULL){
      fprintf(stderr, "game does not exist\n");
      exit(EXIT_FAILURE);
    }
    if (side != N && side != S && side != E && side != W){
      fprintf(stderr, "invalid side (-1 will be returned)\n");
      return -1;
    }
    if(side == E || side == W){
      if(pos>game_height(game) || pos<0){
        fprintf(stderr,"Can't be called out of bound(-1 will be returned)\n");
        return -1;
      }
    }
    if(side == N || side == S){
      if(pos>game_width(game) || pos<0){
        fprintf(stderr,"Can't be called out of bound(-1 will be returned)\n");
        return -1;
      }
    }
    return game->required_nb_seen[side][pos];
  }
  /**
  * @brief get the content of a square in the board
  * @param game the game we consider
  * @param col the column of the square
  * @param line the line of the square
  * @return the content of the square
  **/

  content get_content(cgame game, int col, int line){ // Alexis
    if (col >= game_width(game) || col < 0){
      fprintf (stderr, "Invalid col argument sent to get_content! (col is %d while width is %d)\n", col, game_width(game));
      exit(EXIT_FAILURE);
    }
    if (line >= game_height(game) || line < 0){
      fprintf (stderr, "Invalid line argument sent to get_content! (line is %d while height is %d)\n", line, game_height(game));
      exit(EXIT_FAILURE);
    }
    if (game == NULL){
      fprintf (stderr, "Invalid game argument sent to get_content!\n");
      exit(EXIT_FAILURE);
    }
    return game->board[line*game_width(game)+col];
  }

  /**
  * @brief indicates the aimed number of a given monster on the board
  * @param game the game that you want to collect the information about
  * @param monster the type of monster (should be GHOST, VAMPIRE, ZOMBIE or SPIRIT)
  * @return the number of monsters of that type that should be placed on the game.
  **/

  int required_nb_monsters(cgame game, content monster){
    if (game == NULL){
      fprintf(stderr, "Invalid cgame pointer sent to required_nb_monsters!\n");
      exit(EXIT_FAILURE);
    }
    int monsters=0;
    switch(monster){
      case ZOMBIE :
      monsters=game->required_nb_zombies;
      break;

      case GHOST :
      monsters=game->required_nb_ghosts;
      break;

      case VAMPIRE :
      monsters=game->required_nb_vampires;
      break;

      case SPIRIT :
      monsters=game->required_nb_spirits;
      break;

      case EMPTY :
      fprintf(stderr,"Can't be called over an \"EMPTY\" content");
      exit(EXIT_FAILURE);
      break;
      case MIRROR :
      fprintf(stderr,"Can't be called over a \"MIRROR\" content");
      exit(EXIT_FAILURE);
      break;

      case ANTIMIRROR :
      fprintf(stderr,"Can't be called over an \"ANTIMIRROR\" content");
      exit(EXIT_FAILURE);
      break;

      case HMIRROR :
      fprintf(stderr,"Can't be called over an \"HMIRROR\" content");
      exit(EXIT_FAILURE);
      break;

      case VMIRROR :
      fprintf(stderr,"Can't be called over an \"VMIRROR\" content");
      exit(EXIT_FAILURE);
      break;

    }
    return monsters;
  }

  /**
  * @brief Test if the game is over (that is the grid is filled according to the requirements).
  * @return true if all the constraints are satisfied
  **/

  bool is_game_over (cgame g){
    if(g==NULL){
      fprintf(stderr, "Invalid argument");
      exit(EXIT_FAILURE);
    }

    /* printf("\n\nSCAN /!\\\n\n");
    printf("required_nb_monsters ZOMBIE : %d | current_nb_monsters ZOMBIE : %d\n", required_nb_monsters(g, ZOMBIE), current_nb_monsters(g, ZOMBIE));
    printf("required_nb_monsters VAMPIRE : %d | current_nb_monsters VAMPIRE : %d\n", required_nb_monsters(g, VAMPIRE), current_nb_monsters(g, VAMPIRE));
    printf("required_nb_monsters GHOST : %d | current_nb_monsters GHOST : %d\n", required_nb_monsters(g, GHOST), current_nb_monsters(g, GHOST));
    printf("required_nb_monsters SPIRIT : %d | current_nb_monsters SPIRIT : %d\n", required_nb_monsters(g, SPIRIT), current_nb_monsters(g, SPIRIT));
    for(int i=0; i<game_width(g); i++){
    printf("required_nb_seen N %d : %d | current_nb_seen N %d : %d\n", i, required_nb_seen(g, N, i), i, current_nb_seen(g, N, i));
    printf("required_nb_seen S %d : %d | current_nb_seen S %d : %d\n", i, required_nb_seen(g, S, i), i, current_nb_seen(g, S, i));
  }
  for(int i=0; i<game_height(g); i++){
  printf("required_nb_seen E %d : %d | current_nb_seen E %d : %d\n", i, required_nb_seen(g, E, i), i, current_nb_seen(g, E, i));
  printf("required_nb_seen W %d : %d | current_nb_seen W %d : %d\n", i, required_nb_seen(g, W, i), i, current_nb_seen(g, W, i));
}
printf("\n\nFin_SCAN\n\n");  
*/
if(required_nb_monsters(g, ZOMBIE)!=current_nb_monsters(g, ZOMBIE) || required_nb_monsters(g, GHOST)!=current_nb_monsters(g, GHOST) || required_nb_monsters(g, VAMPIRE)!=current_nb_monsters(g, VAMPIRE) || required_nb_monsters(g, SPIRIT)!=current_nb_monsters(g, SPIRIT)){
  return false;
}
for(int i=0; i<game_width(g); i++){
  if (required_nb_seen(g, N, i)!=current_nb_seen(g, N, i) || required_nb_seen(g, S, i)!=current_nb_seen(g, S, i)){
    return false;
  }
}
for(int i=0; i<game_height(g); i++){
  if (required_nb_seen(g, E, i)!=current_nb_seen(g, E, i) || required_nb_seen(g, W, i)!=current_nb_seen(g, W, i)){
    return false;
  }
}
return true;
}

/**
* @brief Restart a game by cleaning monsters from the board.
**/

void restart_game(game g){
  if(g==NULL){
    fprintf(stderr, "Invalid argument");
    exit(EXIT_FAILURE);
  }
  for (int i=0; i<game_width(g)*game_height(g); i++){
    if (g->board[i]==GHOST || g->board[i]==VAMPIRE || g->board[i]==ZOMBIE || g->board[i]==SPIRIT){
      g->board[i]=EMPTY;
    }
  }
}


/**
* @brief adds a monster on the game board.
* Can also be used to remove any monster by adding EMPTY.
* This function does not have effect on mirrors so it can be used safely in the course of the game.
* @param game the game board where to add the monster
* @param monster the type of monster to add
* @param col the column where to insert the monster
* @param line and the line where to insert the monster
* @return false if the monster was not placed since the square was occupied by a mirror.
**/

bool add_monster(game game, content monster, int col, int line){
  if (game == NULL){
    fprintf(stderr,"Game does not exist\n");
    return false;
  }
  if (col>=game_width(game) || line >=game_height(game) || col<0 || line <0){
    return false;
  }
  if (get_content(game, col, line)==MIRROR || get_content(game,col,line)==ANTIMIRROR || get_content(game,col,line)==HMIRROR || get_content(game,col,line)==VMIRROR){
    return false;
  }
  else{
    game->board[game_width(game)*line + col]=monster;
    return true;
  }
}


/**
* @brief says how many monsters can be seen on the current game board
* @param game the game board to look at
* @param side the side of the board we consider (N, S, W, or E)
* @param pos the coordinate on that side (from S to N or from W to E)
* @return the number of monsters that can be seen through all the mirrors from a given side at position x
**/

int current_nb_seen(cgame game, direction side, int pos){ // Alexis
  if (game == NULL){
    fprintf(stderr, "Invalid game argument sent to current_nb_seen!\n");
    exit(EXIT_FAILURE);
  }
  if (pos < 0 || pos > game_width(game)*game_height(game)-1){
    fprintf(stderr, "Invalid pos argument sent to current_nb_seen!\n");
    return -1;
  }

  int direction_tab_x[4] = {0, 0, -1, 1};                      //Sud, Nord, Ouest, Est
  int direction_tab_y[4] = {-1, 1, 0, 0};
  int direction, x, y;

  switch (side){
    case N:
    x = pos;
    y = game_height(game)-1;
    direction = 0;                                             //direction sud, x prendra x=x et y prendra y-=1
    break;
    case S:
    x = pos;
    y = 0;
    direction = 1;                                             //direction nord, x prendra x=x et y prendra y+=1
    break;
    case E:
    x = game_width(game)-1;
    y = pos;
    direction = 2;                                             //etc..
    break;
    case W:
    x = 0;
    y = pos;
    direction = 3;
    break;
    default:
    fprintf(stderr, "Invalid side argument sent to current_nb_seen!\n");
    exit(EXIT_FAILURE);
    break;
  }                                                            //en bref on donne une direction et une position de départ en fonction des arguments side et pos


  bool mirror_crossed = false;
  int res = 0;
  content content;

  while (x < game_width(game) && y < game_height(game) && x>=0 && y>=0){                     //tant qu'on ne sort pas du board
  content = get_content(game, x, y);                         //on regarde le contenu de la case
  if (content == ZOMBIE){ res++; }
  else if (content == GHOST && mirror_crossed){ res++; }
  else if (content == VAMPIRE && !mirror_crossed){ res++; }  //on ajoute 1 au résultat en fonction du monstre et de si on a rencontré un mirrior
  else if (content == MIRROR) {
    switch (direction){
      case 0:
      direction = 2;
      break;
      case 1:
      direction = 3;
      break;
      case 2:
      direction = 0;
      break;
      case 3:
      direction = 1;
      break;
    }
    mirror_crossed = true;
  }                                                          //on met à jour la direction si on rencontre un mirrior
  else if (content == ANTIMIRROR) {
    switch (direction){
      case 0:
      direction = 3;
      break;
      case 1:
      direction = 2;
      break;
      case 2:
      direction = 1;
      break;
      case 3:
      direction = 0;
      break;
    }
    mirror_crossed = true;
  }
  else if (content == HMIRROR) {
    switch (direction){
      case 0:
      direction = 1;
      mirror_crossed = true;
      break;
      case 1:
      direction = 0;
      mirror_crossed = true;
      break;
      case 2:
      break;
      case 3:
      break;
    }
  }
  else if (content == VMIRROR) {
    switch (direction){
      case 0:
      break;
      case 1:
      break;
      case 2:
      direction = 3;
      mirror_crossed = true;
      break;
      case 3:
      direction = 2;
      mirror_crossed = true;
      break;
    }
  }                                                      //de même pour un anti-mirroir
  x += direction_tab_x[direction];
  y += direction_tab_y[direction];                           //on met à jour x et y en fonction de la direction
}
return res;
}

/**
* @brief counts the current number of monsters of a given type
* @param game the game board
* @param monster the type of monster
* @return the total number of monsters of the given type on the board.
**/

int current_nb_monsters(cgame game, content monster){
  if (game == NULL){
    exit(EXIT_FAILURE);
  }
  if(monster !=ZOMBIE && monster!=GHOST && monster !=VAMPIRE && monster !=SPIRIT){
    fprintf(stderr,"Function called over an invalid monster");
    return -1;
  }
  int cpt=0;
  for (int i = 0; i<game_width(game)*game_height(game); i++){
    if (game->board[i]==monster)
    cpt++;
  }
  return cpt;
}
