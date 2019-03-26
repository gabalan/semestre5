
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "game.h"

bool test_add_monster(){
   game jeu= new_game();
   bool rep=true;
   assert(jeu);
   add_monster(jeu,ZOMBIE,0,1);
   add_monster(jeu,ZOMBIE,1,0);
   add_monster(jeu,GHOST,2,0);
   add_monster(jeu,GHOST,1,1);
   add_monster(jeu,ZOMBIE,1,2);
   add_monster(jeu,ZOMBIE,2,2);
   add_monster(jeu,ZOMBIE,2,3);
   add_monster(jeu,VAMPIRE,1,3);
   add_monster(jeu,VAMPIRE,3,2);

if((get_content(jeu, 0, 1) != ZOMBIE)|| (get_content(jeu, 1, 0) != ZOMBIE)||(get_content(jeu, 2, 0) != GHOST)||(get_content(jeu, 1, 1) != GHOST)||(get_content(jeu, 1,2 ) != ZOMBIE) ||(get_content(jeu, 2,2 ) != ZOMBIE) ||(get_content(jeu, 2,3 ) != ZOMBIE) ||(get_content(jeu, 1,3 ) != VAMPIRE) ||(get_content(jeu, 3,2 ) != VAMPIRE)){
      fprintf(stderr,("Basic test on get_content failed\n"));
      delete_game(jeu);
      rep=false;
  }
  delete_game(jeu);
  return rep;

}


bool test_is_game_over (){
      game jeu =new_game ();
       bool rep=true;
   	assert(jeu);
      add_mirror(jeu, 1, 0, 3);
      add_mirror(jeu, 0, 3, 3);
      add_mirror(jeu, 1, 0, 2);
      add_mirror(jeu, 1, 2, 1);
      add_mirror(jeu, 0, 3, 1);
      add_mirror(jeu, 1, 0, 0);
      add_mirror(jeu, 1, 3, 0);

      add_monster(jeu,ZOMBIE,0,1);
      add_monster(jeu,ZOMBIE,1,0);
      add_monster(jeu,GHOST,2,0);
      add_monster(jeu,GHOST,1,1);
      add_monster(jeu,ZOMBIE,1,2);
      add_monster(jeu,ZOMBIE,2,2);
      add_monster(jeu,ZOMBIE,2,3);
      add_monster(jeu,VAMPIRE,1,3);
      add_monster(jeu,VAMPIRE,3,2);

      set_required_nb_monsters(jeu, ZOMBIE,5);
      set_required_nb_monsters(jeu, VAMPIRE,2);
      set_required_nb_monsters(jeu, GHOST,2);

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
      if(test_add_monster ()==false){
          if((get_content(jeu,0,3)!=ANTIMIRROR) || (get_content(jeu,3,3)!=MIRROR) || (get_content(jeu,0,2)!=ANTIMIRROR) ||(get_content(jeu,2,1)!=ANTIMIRROR) || (get_content(jeu,3,1)!=MIRROR) || (get_content(jeu,0,0)!=ANTIMIRROR) || (get_content(jeu,3,0)!=ANTIMIRROR)){
                 if(required_nb_monsters(jeu, ZOMBIE)!=5 || required_nb_monsters(jeu,VAMPIRE)!=2||required_nb_monsters(jeu, GHOST)!=2){
                      delete_game(jeu);
                     fprintf(stderr,("Basic test on is_game_over failed\n"));
                     rep=false ;
                 }
            }

     }

     delete_game(jeu);
     return rep;

}

     




int main(void){
  bool result = true;
  result =  test_is_game_over () && result;
  if(result){
      printf("Tests successfull\n");
      return EXIT_SUCCESS;
  }
  else{
      printf("Tests failed\n");
      return EXIT_FAILURE;
  }
}
