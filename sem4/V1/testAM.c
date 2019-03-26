#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "game_io.h"
#include "game.h"

#define NB_DIR 4
#define NB_COL 4
#define NB_LINE 4


bool rep=true;
bool test_new_game_ext(){
  bool rep=true;
  game jeu = new_game_ext(NB_COL,NB_LINE);
  assert(jeu);
  if(game_width(jeu) != NB_COL || game_height(jeu) != NB_LINE){
    fprintf(stderr, "erreur au niveau de height et width de la fonction new_game_ext \n");
  }
 	for (int i=0; i < NB_COL; i++){
 		for(int j=0;j < NB_LINE;j++){
 			if(get_content(jeu, i, j)!=EMPTY){
 				rep = false;
 				fprintf(stderr,("Error new_game_ext les cases ne sont pas vides\n"));
        delete_game (jeu);
        return false;
      }
    }
  }

  for(int i = 0; i < NB_DIR; i++){
    if(required_nb_seen(jeu, N,i) != 0 || required_nb_seen(jeu, S,i) != 0  || required_nb_seen(jeu, E,i) != 0 || required_nb_seen(jeu, W,i) != 0){
      fprintf(stderr, "error au niveau de required_nb_seen \n");
      rep = false;
    }
  }
  if(required_nb_monsters(jeu, ZOMBIE) != 0 || required_nb_monsters (jeu, VAMPIRE) != 0 || required_nb_monsters (jeu, GHOST)  != 0 || required_nb_monsters(jeu ,SPIRIT) != 0){
    fprintf(stderr, "error au niveau de required_nb_monsters \n");
    rep = false;
  }
  delete_game(jeu);
  return rep;

}

bool test_add_monster(){
   game jeu= new_game_ext(NB_COL,NB_LINE);
   assert(jeu);
   add_monster(jeu,VAMPIRE,0,1);
   add_monster(jeu,ZOMBIE,1,0);
   add_monster(jeu,GHOST,2,0);
   add_monster(jeu,SPIRIT,1,1);

   if(get_content(jeu,0,1) != VAMPIRE || get_content(jeu, 1,0) != ZOMBIE || get_content(jeu, 2,0) != GHOST || get_content(jeu,1,1) != SPIRIT){
     fprintf(stderr, "error in function add_monster 2 \n");
     delete_game(jeu);
     return false;
   }
   if(add_monster(jeu,VAMPIRE, 0, 1) != true || add_monster(jeu,VAMPIRE, 1, 0) != true || add_monster(jeu,VAMPIRE,2, 0) != true || add_monster(jeu,VAMPIRE, 1, 1) != true){
     fprintf(stderr, "error in function add_monster 1 \n");
     delete_game(jeu);
     return false;

   }
  delete_game(jeu);
  return true;
}

bool test_add_mirror_ext(){
  game jeu = new_game_ext(NB_COL,NB_LINE);
  assert(jeu);
  add_mirror_ext(jeu, ANTIMIRROR,0,3);
  add_mirror_ext(jeu, MIRROR,3,3);
  add_mirror_ext(jeu, VMIRROR,0,2);
  add_mirror_ext(jeu, HMIRROR,0,0);

  if(get_content(jeu,0,3) != ANTIMIRROR ||get_content(jeu,3,3) != MIRROR || get_content(jeu,0,2) != VMIRROR  || get_content(jeu,0,0) != HMIRROR  ){
    fprintf(stderr, "erro in add_mirror_ext \n");
    delete_game(jeu);
    rep = false;
  }
  delete_game(jeu);
  return rep;

}


bool test_is_game_over (){
    bool rep = true;
      game jeu =new_game ();
      assert(jeu);
      if(is_game_over(jeu) == false){
        fprintf(stderr,"error in is_game_over 1 \n");
        rep = false;
      }

      add_mirror_ext(jeu, ANTIMIRROR, 0, 3);
      add_mirror_ext(jeu, MIRROR, 3, 3);
      add_mirror_ext(jeu,ANTIMIRROR, 0, 2);
      add_mirror_ext(jeu, ANTIMIRROR, 2, 1);
      add_mirror_ext(jeu, MIRROR, 3, 1);
      add_mirror_ext(jeu, ANTIMIRROR, 0, 0);
      add_mirror_ext(jeu, ANTIMIRROR, 3, 0);

      add_monster(jeu,ZOMBIE,0,1);
      add_monster(jeu,ZOMBIE,1,0);
      add_monster(jeu,GHOST,2,0);
      add_monster(jeu,GHOST,1,1);
      add_monster(jeu,ZOMBIE,1,2);
      add_monster(jeu,ZOMBIE,2,2);
      add_monster(jeu,ZOMBIE,3,2);
      add_monster(jeu,VAMPIRE,1,3);
      add_monster(jeu,VAMPIRE,2,3);


      set_required_nb_monsters(jeu, ZOMBIE,5);
      set_required_nb_monsters(jeu, VAMPIRE,2);
      set_required_nb_monsters(jeu, GHOST,2);
      set_required_nb_monsters(jeu,SPIRIT,0);

      set_required_nb_seen(jeu, N, 0, 0);
      set_required_nb_seen(jeu, N, 1, 3);
      set_required_nb_seen(jeu, N, 2, 3);
      set_required_nb_seen(jeu, N, 3, 0);

      set_required_nb_seen(jeu, S, 0, 0);
      set_required_nb_seen(jeu, S, 1, 3);
      set_required_nb_seen(jeu, S, 2, 2);
      set_required_nb_seen(jeu, S, 3, 3);

      set_required_nb_seen(jeu, W, 3, 3);
      set_required_nb_seen(jeu, W, 2, 3);
      set_required_nb_seen(jeu, W, 1, 2);
      set_required_nb_seen(jeu, W, 0, 0);

      set_required_nb_seen(jeu, E, 3, 2);
      set_required_nb_seen(jeu, E, 2, 3);
      set_required_nb_seen(jeu, E, 1, 0);
      set_required_nb_seen(jeu, E, 0, 0);


      if(is_game_over(jeu) == false){
        fprintf(stderr, "erreur sur la fonction is_game_over \n");
        rep = false;
      }
     delete_game(jeu);
     return rep;
}

bool test_restart_game(){
  game jeu = new_game_ext(NB_COL,NB_LINE);
  assert(jeu);
  add_monster(jeu,VAMPIRE,0,1);
  add_monster(jeu,ZOMBIE,1,0);
  add_monster(jeu,GHOST,2,0);
  add_monster(jeu,SPIRIT,1,1);

  restart_game(jeu);

  if(get_content(jeu,0,1) != EMPTY || get_content(jeu, 1,0) != EMPTY || get_content(jeu, 2,0) != EMPTY || get_content(jeu,1,1) != EMPTY){
    fprintf(stderr, "error in function add_monster");
    rep = false;
  }
  delete_game(jeu);
  return rep;

}
bool test_game_width(){
  game jeu = new_game_ext(NB_COL,NB_LINE);
  assert(jeu);
  if(game_width(jeu) != NB_COL){
    fprintf(stderr, "error in function game_width");
    rep = false;
  }
  delete_game(jeu);
  return rep;
}
bool test_game_height(){
  game jeu = new_game_ext(NB_COL,NB_LINE);
  assert(jeu);
  if(game_height(jeu) != NB_LINE){
    fprintf(stderr, "error in function game_height");
    rep = false;
  }
  delete_game(jeu);
  return rep;
}


bool test_copy_game(){
  game jeu = new_game_ext(NB_COL,NB_LINE);
    assert(jeu);
    game copy = copy_game(jeu);
    assert(jeu);
    if(required_nb_monsters(jeu,ZOMBIE) != required_nb_monsters(copy,ZOMBIE) || required_nb_monsters(jeu,VAMPIRE) != required_nb_monsters(copy,VAMPIRE) || required_nb_monsters(jeu,GHOST) != required_nb_monsters(copy,GHOST) || required_nb_monsters(jeu,SPIRIT) != required_nb_monsters(copy,SPIRIT)){
      fprintf(stderr, "error in function copy_game");
      rep = false;
    }
    if(game_width(jeu) != game_width(copy) || game_height(jeu) != game_height(copy)){
      fprintf(stderr, "error in function game_height");
      rep = false;
    }
    for (int i = 0; i < NB_DIR; i++){
    if ((required_nb_seen(jeu, S, i) != required_nb_seen(copy, S, i)) || (required_nb_seen(jeu, N, i) != required_nb_seen(copy, N, i)) || (required_nb_seen(jeu, W, i) != required_nb_seen(copy, W, i)) || (required_nb_seen(jeu, E, i) != required_nb_seen(copy, E, i))){
      fprintf(stderr, "echec on copy les labels sont differents");
      rep = false;
    }
  }
  for (int i = 0; i < NB_COL; i++){
    for (int j = 0; j < NB_LINE; j++){
      if (get_content(jeu, j, i) != get_content(copy, j, i)){
        fprintf(stderr, "echec in copy les cases sont differents");
        rep = false;
      }
    }
  }
  delete_game(jeu);
  delete_game(copy);
  return rep;
}


int main(void){
  bool result = true;
  result = test_new_game_ext() && result;
  result =  test_is_game_over () && result;
  result = test_add_mirror_ext() && result;
  result = test_copy_game() && result;
  result = test_add_mirror_ext() && result;
  result =  test_restart_game () && result;
  result = test_game_width() && result;
  result = test_game_height() && result;
  result = test_add_monster() && result;
  if(result){
      printf("Tests successfull\n");
      return EXIT_SUCCESS;
  }
  else{
      printf("Tests failed\n");
      return EXIT_FAILURE;
  }
}
