#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "game_io.h"
#include "game.h"

bool test_new_game(){
 bool res = true;
  game g = new_game();
  if (!g){
    fprintf(stderr,"Game is not created in test_new_game !\n");
    res = false;
  }
  if ((required_nb_monsters(g, ZOMBIE) != 0) || (required_nb_monsters(g, GHOST) != 0) || (required_nb_monsters(g, VAMPIRE) != 0)){
    fprintf(stderr, "Number of monster not equal to 0 in test_new_game !\n");
    res = false;
  }
  for (int i = 0; i < NB_DIR ; i++){
    if ((required_nb_seen(g, S, i) != 0) || (required_nb_seen(g, N, i) != 0) || (required_nb_seen(g, W, i) != 0) || (required_nb_seen(g, E, i) != 0)){
      fprintf(stderr, "Labels not equal to 0 in test_new_game!\n");
      res = false;
    }
  }
  for (int i = 0; i < NB_DIR; i++){
    for (int j = 0; j < NB_DIR; j++){
      if (get_content(g, j, i) != EMPTY){
    fprintf(stderr, "Some cases of the game board are not EMPTY in test_new_game !\n");
	res = false;
      }
    }
  }
  delete_game(g);
  return res;
}

bool test_new_game_ext(){
  bool res = true;
  int w=0, h=0;
  game g = new_game_ext(4,4);
  if (!g){
    fprintf(stderr,"Game not created in test_new_game!\n");
    res = false;
  }
  if ((required_nb_monsters(g, ZOMBIE) != 0) || (required_nb_monsters(g, GHOST) != 0) || (required_nb_monsters(g, VAMPIRE) != 0) || (required_nb_monsters(g, SPIRIT) != 0)){
    fprintf(stderr, "Number of monster not equal to 0 in test_new_game_ext !\n");
    res = false;
  }
  for (int i = 0; i < NB_DIR ; i++){
    if ((required_nb_seen(g, S, i) != 0) || (required_nb_seen(g, N, i) != 0) || (required_nb_seen(g, W, i) != 0) || (required_nb_seen(g, E, i) != 0)){
      fprintf(stderr, "Labels are not equal to 0 in test_new_game_ext !\n");
      res = false;
    }
  }
  for (int i = 0; i < NB_DIR; i++){
    w=w+1;
    for (int j = 0; j < NB_DIR; j++){
      h=h+1;
      if (get_content(g, j, i) != EMPTY){
    fprintf(stderr, "Some cases of game board are not EMPTY in test_new_game_ext !\n");
	res = false;
      }
    }
  }
  if (w!=game_width(g) || h!=game_height(g)*game_width(g)){
    fprintf(stderr, "width or height not good");
    res = false;
  }
  delete_game(g);
  return res;
}

bool test_delete_game(){
  bool res = true;
  game g = new_game();
  assert(g);
  delete_game(g);
  return res;
}

bool test_get_content(){
  bool res = true;
  game g = new_game();
  assert(g);
  add_monster(g, VAMPIRE, 1, 3);
  if (get_content(g, 1, 3) != VAMPIRE){
    fprintf(stderr, "The content of the board is indeterminate in get_content !\n");
    res = false;
  }
  delete_game(g);
  return res;
}

bool test_add_mirror(){
  game g = new_game();
  assert(g);
  add_mirror(g, 1, 0, 1);
  add_mirror(g, 0, 1, 0);
  if ((get_content(g, 0, 1) != ANTIMIRROR) || (get_content(g, 1, 0) != MIRROR)){
    fprintf(stderr, "cannot place a mirror in add_mirror !\n");
    return false;
  }
  delete_game(g);
  return true;
}

bool test_add_mirror_ext(){
  game g = new_game();
  assert(g);
  add_mirror_ext(g, MIRROR, 0, 0);
  if (get_content(g, 0, 0) != MIRROR){
    fprintf(stderr, "cannot place a mirror in test_add_mirror_ext\n");
    return false;
  }
  add_mirror_ext(g, ANTIMIRROR, 0, 0);
  if (get_content(g, 0, 0) != ANTIMIRROR){
    fprintf(stderr, "cannot place an antimirror in test_add_mirror_ext\n");
    return false;
  }
  add_mirror_ext(g, VMIRROR, 0, 0);
  if (get_content(g, 0, 0) != VMIRROR){
    fprintf(stderr, "cannot place a vertical mirror in test_add_mirror_ext\n");
    return false;
  }
  add_mirror_ext(g, HMIRROR, 0, 0);
  if (get_content(g, 0, 0) != HMIRROR){
    fprintf(stderr, "cannot place a horizontal mirror in test_add_mirror_ext\n");
    return false;
  }
  delete_game(g);
  return true;
}

bool test_all_required_nb_seen(){
  bool res = true;
  game g = new_game();
  assert(g);
  set_required_nb_seen(g, S, 1, 3);
  if (required_nb_seen(g, S, 1) != 3){
    fprintf(stderr,"Test on labels failed in test_all_required_nb_seen !\n");
    res = false;
  }
  delete_game(g);
  return res;
}

bool test_all_required_nb_monsters(){
  bool res = true;
  game g = new_game();
  assert(g);
  set_required_nb_monsters(g, VAMPIRE, 2);
  set_required_nb_monsters(g, GHOST, 2);
  set_required_nb_monsters(g, ZOMBIE, 5);
  set_required_nb_monsters(g, SPIRIT, 0);
  if ((required_nb_monsters(g, VAMPIRE) != 2) || (required_nb_monsters(g, GHOST) != 2) || (required_nb_monsters(g, ZOMBIE) != 5) || (required_nb_monsters(g, SPIRIT)!=0)){
    fprintf(stderr,"Test on number of monster failed in test_all_required_nb_monsters !\n");
    res = false;
  }
  delete_game(g);
  return res;
}

bool test_setup_new_game(){
  bool res = true;
  int* labels[NB_DIR];
  int coordinate[16] = {0,3,3,0,0,3,2,3,0,0,3,2,0,2,3,3};
  int* labelsN = coordinate;
  int* labelsS = coordinate + 4;
  int* labelsE = coordinate + 8;
  int* labelsW = coordinate + 12;
  labels[0] = labelsN;
  labels[1] = labelsS;
  labels[2] = labelsE;
  labels[3] = labelsW;
  content* board = (content*) malloc((NB_DIR*NB_DIR)*sizeof(content));
  if(!board){
	fprintf(stderr,"Not enough memory to create a game board on test_setup_new_game");
	return false;
  }
  board[0] = ANTIMIRROR;
  board[1] = EMPTY;
  board[2] = EMPTY;
  board[3] = ANTIMIRROR;
  board[4] = EMPTY;
  board[5] = EMPTY;
  board[6] = ANTIMIRROR;
  board[7] = MIRROR;
  board[8] = ANTIMIRROR;
  board[9] = EMPTY;
  board[10] = EMPTY;
  board[11] = EMPTY;
  board[12] = ANTIMIRROR;
  board[13] = EMPTY;
  board[14] = EMPTY;
  board[15] = MIRROR;
  int ghosts = 2;
  int vampires = 2;
  int zombies = 5;
  game g = setup_new_game(labels, board, ghosts, vampires, zombies);
  assert(g);
  if(required_nb_monsters(g,GHOST)!=2 || required_nb_monsters(g,VAMPIRE)!=2 || required_nb_monsters(g,ZOMBIE)!=5){
    fprintf(stderr,"Number of monsters not correct at initialization in test_setup_new_game !\n");
    res=false;
  }
  if(required_nb_seen(g, S, 0)!=0 || required_nb_seen(g, S, 1)!=3 || required_nb_seen(g, S, 2)!=2 || required_nb_seen(g, S, 3)!=3 || required_nb_seen(g, N, 0)!=0 || required_nb_seen(g, N, 1)!=3 || required_nb_seen(g, N, 2)!=3 || required_nb_seen(g, N, 3)!=0 || required_nb_seen(g, W, 0)!=0 || required_nb_seen(g, W, 1)!=2 || required_nb_seen(g, W, 2)!=3 || required_nb_seen(g, W, 3)!=3 || required_nb_seen(g, E, 0)!=0 || required_nb_seen(g, E, 1)!=0 || required_nb_seen(g, E, 2)!=3 || required_nb_seen(g, E, 3)!=2){
    fprintf(stderr,"Labels not correct at initialisation in test_setup_new_game !\n");
    res=false;
  }
  if(get_content(g,0,0)!= ANTIMIRROR || get_content(g,0,1)!= EMPTY || get_content(g,0,2)!= ANTIMIRROR || get_content(g,0,3)!= ANTIMIRROR || get_content(g,1,0)!= EMPTY || get_content(g,1,1)!= EMPTY || get_content(g,1,2)!= EMPTY || get_content(g,1,3)!= EMPTY || get_content(g,2,0)!= EMPTY || get_content(g,2,1)!= ANTIMIRROR || get_content(g,2,2)!= EMPTY || get_content(g,2,3)!= EMPTY || get_content(g,3,0)!= ANTIMIRROR || get_content(g,3,1)!= MIRROR || get_content(g,3,2)!= EMPTY || get_content(g,3,3)!= MIRROR){
    fprintf(stderr,"The game board not correct at initialisation in test_setup_new_game !\n");
    res=false;
  }
  free(board);
  delete_game(g);
  return res;
}

bool test_setup_new_game_ext(){
    bool res = true;
    int* labels[NB_DIR];
    int coordinate[16] = {0,3,3,0,0,3,2,3,0,0,3,2,0,2,3,3};
    int* labelsN = coordinate;
    int* labelsS = coordinate + 4;
    int* labelsE = coordinate + 8;
    int* labelsW = coordinate + 12;
    labels[0] = labelsN;
    labels[1] = labelsS;
    labels[2] = labelsE;
    labels[3] = labelsW;
    content* board = (content*) malloc((NB_DIR*NB_DIR)*sizeof(content));
    if(!board){
      fprintf(stderr,"Not enough memory to create a game board on test_setup_new_game_ext");
      return false;
    }
    board[0] = ANTIMIRROR;
    board[1] = EMPTY;
    board[2] = EMPTY;
    board[3] = ANTIMIRROR;
    board[4] = EMPTY;
    board[5] = EMPTY;
    board[6] = ANTIMIRROR;
    board[7] = MIRROR;
    board[8] = ANTIMIRROR;
    board[9] = EMPTY;
    board[10] = EMPTY;
    board[11] = EMPTY;
    board[12] = ANTIMIRROR;
    board[13] = EMPTY;
    board[14] = EMPTY;
    board[15] = MIRROR;
    int ghosts = 2;
    int vampires = 2;
    int zombies = 5;
    int spirits = 3;
    game g = setup_new_game_ext(4,4,labels, board, ghosts, vampires, zombies, spirits);
    assert(g);
    if(required_nb_monsters(g,GHOST)!=2 || required_nb_monsters(g,VAMPIRE)!=2 || required_nb_monsters(g,ZOMBIE)!=5 || required_nb_monsters(g,SPIRIT)!=3){
      fprintf(stderr,"Number of monster not correct at initialization in test_setup_new_game_ext !\n");
      res=false;
    }
    if(required_nb_seen(g, S, 0)!=0 || required_nb_seen(g, S, 1)!=3 || required_nb_seen(g, S, 2)!=2 || required_nb_seen(g, S, 3)!=3 || required_nb_seen(g, N, 0)!=0 || required_nb_seen(g, N, 1)!=3 || required_nb_seen(g, N, 2)!=3 || required_nb_seen(g, N, 3)!=0 || required_nb_seen(g, W, 0)!=0 || required_nb_seen(g, W, 1)!=2 || required_nb_seen(g, W, 2)!=3 || required_nb_seen(g, W, 3)!=3 || required_nb_seen(g, E, 0)!=0 || required_nb_seen(g, E, 1)!=0 || required_nb_seen(g, E, 2)!=3 || required_nb_seen(g, E, 3)!=2){
      fprintf(stderr,"Labels not correct at initialisation in test_setup_new_game_ext !\n");
      res=false;
    }
    if(get_content(g,0,0)!= ANTIMIRROR || get_content(g,0,1)!= EMPTY || get_content(g,0,2)!= ANTIMIRROR || get_content(g,0,3)!= ANTIMIRROR || get_content(g,1,0)!= EMPTY || get_content(g,1,1)!= EMPTY || get_content(g,1,2)!= EMPTY || get_content(g,1,3)!= EMPTY || get_content(g,2,0)!= EMPTY || get_content(g,2,1)!= ANTIMIRROR || get_content(g,2,2)!= EMPTY || get_content(g,2,3)!= EMPTY || get_content(g,3,0)!= ANTIMIRROR || get_content(g,3,1)!= MIRROR || get_content(g,3,2)!= EMPTY || get_content(g,3,3)!= MIRROR){
      fprintf(stderr,"The game board not correct at initialisation in test_setup_new_game_ext !\n");
      res=false;
    }
    free(board);
    delete_game(g);
    return res;
}

bool test_copy_game(){
  bool res = true;
  game g_src = new_game();
  assert(g_src);
  game copy = copy_game(g_src);
  if (!copy){
    fprintf(stderr,"Copy of the game not created in test_copy_game !\n");
    res = false;
  }
  if ((required_nb_monsters(g_src, ZOMBIE) != required_nb_monsters(copy, ZOMBIE)) || (required_nb_monsters(g_src, GHOST) != required_nb_monsters(copy, GHOST)) || (required_nb_monsters(g_src, VAMPIRE) != required_nb_monsters(copy, VAMPIRE))){
    fprintf(stderr, "copy is different (number of monsters) in test_copy_game !\n");
    res = false;
  }
  for (int i = 0; i < NB_DIR; i++){
    if ((required_nb_seen(g_src, S, i) != required_nb_seen(copy, S, i)) || (required_nb_seen(g_src, N, i) != required_nb_seen(copy, N, i)) || (required_nb_seen(g_src, W, i) != required_nb_seen(copy, W, i)) || (required_nb_seen(g_src, E, i) != required_nb_seen(copy, E, i))){
      fprintf(stderr, "copy is different (labels) in test_copy_game !\n");
      res = false;
    }
  }
  for (int i = 0; i < NB_DIR; i++){
    for (int j = 0; j < NB_DIR; j++){
      if (get_content(g_src, j, i) != get_content(copy, j, i)){
	fprintf(stderr, "copy is different (board content) in test_copy_game !\n");
	res = false;
      }
    }
  }
  delete_game(g_src);
  delete_game(copy);
  return res;
}

bool test_add_monster(){
  game g = new_game();
  assert(g);
  if (add_monster(g, GHOST, 1, 1) != true){
    fprintf(stderr,"add_monster must return true if the monster can be placed in test_add_monster !\n");
    return false;
  }
  add_monster(g, GHOST, 1, 1);
  if (get_content(g, 1, 1) != GHOST){
    fprintf(stderr,"Add a monster failed in test_add_monster!\n");
    return false;
  }
  add_mirror(g, 1, 0, 0);
  if (add_monster(g, GHOST, 0, 0) != false){
    fprintf(stderr,"add_monster must return false if the monster can't be placed in test_add_monster !\n");
    return false;
  }
  add_monster(g, GHOST, 0, 0);
  if (get_content(g, 0, 0) != ANTIMIRROR){
    fprintf(stderr,"add_monster has replaced a mirror by a monster in test_add_monster !\n");
    return false;
  }
  add_monster(g, EMPTY, 1, 1);
  if (get_content(g, 1, 1) != EMPTY){
    fprintf(stderr,"Removal a monster fail in test_add_monster !\n");
    return false;
  }
  delete_game(g);
  return true;
}

bool test_is_game_over(){
  bool res = true;
  game g = new_game();
  assert(g);
  if (is_game_over(g) != false){
    fprintf(stderr,"test_is_game_over failed for an unfinished game !\n");
    res = false;
  }
  else {
    add_mirror(g, 1, 0, 0);
    add_mirror(g, 1, 3, 0);
    add_mirror(g, 1, 2, 1);
    add_mirror(g, 0, 3, 1);
    add_mirror(g, 1, 0, 2);
    add_mirror(g, 1, 0, 3);
    add_mirror(g, 0, 3, 3);
    set_required_nb_seen(g, S, 1, 3);
    set_required_nb_seen(g, S, 2, 2);
    set_required_nb_seen(g, S, 3, 3);
    set_required_nb_seen(g, N, 1, 3);
    set_required_nb_seen(g, N, 2, 3);
    set_required_nb_seen(g, W, 1, 2);
    set_required_nb_seen(g, W, 2, 3);
    set_required_nb_seen(g, W, 3, 3);
    set_required_nb_seen(g, E, 2, 3);
    set_required_nb_seen(g, E, 3, 2);
    set_required_nb_monsters(g, ZOMBIE, 5);
    set_required_nb_monsters(g, VAMPIRE, 2);
    set_required_nb_monsters(g, GHOST, 2);
    add_monster(g, GHOST, 2, 0);
    add_monster(g, GHOST, 1, 1);
    add_monster(g, VAMPIRE, 1, 3);
    add_monster(g, VAMPIRE, 2, 3);
    add_monster(g, ZOMBIE, 1, 0);
    add_monster(g, ZOMBIE, 0, 1);
    add_monster(g, ZOMBIE, 1, 2);
    add_monster(g, ZOMBIE, 2, 2);
    add_monster(g, ZOMBIE, 3, 2);
    if (is_game_over(g) != true){
      fprintf(stderr,"test_is_game_over failed on a finish game !\n");
      res = false;
    }
  }
  delete_game(g);
  return res;
}

bool test_restart_game(){
  game gibson = new_game();
  assert(gibson);
  add_monster(gibson, GHOST, 1, 1);
  restart_game(gibson);
  if (get_content(gibson, 1, 1) != EMPTY){
    fprintf(stderr,"restart game failed in test_restart_game!\n");
    return false;
  }
  delete_game(gibson);
  return true;
}

bool test_current_nb_seen(){
  game g = new_game();
  assert(g);
  add_mirror(g, 0, 2, 1);
  add_monster(g, ZOMBIE, 0, 1);
  add_monster(g, EMPTY, 1, 1);
  add_monster(g, GHOST, 2, 2);
  add_monster(g, VAMPIRE, 2, 3);
  if (current_nb_seen(g, W, 1) != 2){
    fprintf(stderr,"We can't know the number of visible monster from a given position in test_current_nb_seen !\n");
    return false;
  }
  delete_game(g);
  return true;
}

bool test_current_nb_monsters(){
  game game = new_game();
  assert(game);
  add_monster(game, GHOST, 1, 1);
  add_monster(game, ZOMBIE, 1, 0);
  add_monster(game, VAMPIRE, 1, 3);
  add_monster(game, SPIRIT, 2, 2);
  if ((current_nb_monsters(game, GHOST) != 1) || (current_nb_monsters(game, ZOMBIE) != 1) || (current_nb_monsters(game, VAMPIRE) != 1) || (current_nb_monsters(game,SPIRIT)!=1)){
    fprintf(stderr,"Number of ghost, vampire, spirit or zombie can't be determined in test_current_nb_monsters !\n");
    return false;
  }
  delete_game(game);
  return true;
}

bool test_game_width(){
  game g = new_game_ext(3, 6);
  if(!g){
	fprintf(stderr,"Game not created in setup_new_game_ext\n");
	return false;
  }
  if (game_width(g)!=3){
	fprintf(stderr,"Number of culumns is not right in test_game_widt\n");
	return false;
  }

  delete_game(g);
  return true;

}

bool test_game_height(){
  int* labels[NB_DIR];
  int coordinate[16] = {0,3,3,0,0,3,2,3,0,0,3,2,0,2,3,3};
  int* labelsN = coordinate;
  int* labelsS = coordinate + 4;
  int* labelsE = coordinate + 8;
  int* labelsW = coordinate + 12;
  labels[0] = labelsN;
  labels[1] = labelsS;
  labels[2] = labelsE;
  labels[3] = labelsW;
  content* board = (content*) malloc(24*sizeof(content));
  if(!board){
	fprintf(stderr,"Not enough memory to create game board in test_setup_new_game\n");
	return false;
  }
  board[0] = ANTIMIRROR;
  board[1] = EMPTY;
  board[2] = EMPTY;
  board[3] = ANTIMIRROR;
  board[4] = EMPTY;
  board[5] = EMPTY;
  board[6] = ANTIMIRROR;
  board[7] = MIRROR;
  board[8] = ANTIMIRROR;
  board[9] = EMPTY;
  board[10] = EMPTY;
  board[11] = EMPTY;
  board[12] = ANTIMIRROR;
  board[13] = EMPTY;
  board[14] = EMPTY;
  board[15] = MIRROR;
  int ghosts = 2;
  int vampires = 2;
  int zombies = 4;
  int spirit=1;
  game g = setup_new_game_ext(6, 4,labels, board, ghosts, vampires, zombies,spirit);
  if(!g){
	fprintf(stderr,"game is not created in setup_new_game_ext\n");
	return false;
  }
  if (game_height(g)!=4){
	fprintf(stderr,"Number of line is not right in test_game_height\n");
	return false;
  }
  free(board);
  delete_game(g);
  return true;

}

//bool test_load_game();

//bool test_save_game();

int main(){
  bool megaGG = true;
  megaGG = megaGG && test_new_game() && test_new_game_ext() && test_delete_game() && test_setup_new_game() && test_setup_new_game_ext() && test_add_mirror() && test_add_mirror_ext() && test_all_required_nb_seen() && test_all_required_nb_monsters() && test_copy_game() && test_get_content() && test_is_game_over() && test_restart_game() && test_add_monster() && test_current_nb_seen() && test_current_nb_monsters() && test_game_width() && test_game_height();
  if (megaGG){
    printf("These developers are too strong !\n");
    return EXIT_SUCCESS;
  }
  else {
    printf("These developers have a little drunk !\n");
    return EXIT_FAILURE;
  }
}
