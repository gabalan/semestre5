#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "game.h"


bool rep=true;
bool test_add_mirror(){
     game jeu= new_game();
     assert(jeu);
     add_mirror(jeu, 1, 0, 3);
     add_mirror(jeu, 0, 3, 3);
     add_mirror(jeu, 1, 0, 2);
     add_mirror(jeu, 1, 2, 1);
     add_mirror(jeu, 0, 3, 1);
     add_mirror(jeu, 1, 0, 0);
     add_mirror(jeu, 1, 3, 0);

     if((get_content(jeu,0,3)!=ANTIMIRROR) || (get_content(jeu,3,3)!=MIRROR) || (get_content(jeu,0,2)!=ANTIMIRROR) ||(get_content(jeu,2,1)!=ANTIMIRROR) || (get_content(jeu,3,1)!=MIRROR) || (get_content(jeu,0,0)!=ANTIMIRROR) || (get_content(jeu,3,0)!=ANTIMIRROR))
           {
           fprintf(stderr,("Basic test on add_mirror failed\n"));
           rep= false;
           
           }
     delete_game(jeu);
     return rep;
}
bool test_set_required_nb_monster(){
	game jeu= new_game();
        assert(jeu);
	set_required_nb_monsters(jeu, ZOMBIE,5);
	set_required_nb_monsters(jeu, VAMPIRE,2);
	set_required_nb_monsters(jeu, GHOST,2);
if(required_nb_monsters(jeu, ZOMBIE)!=5 || required_nb_monsters(jeu,VAMPIRE)!=2||required_nb_monsters(jeu, GHOST)!=2){
	fprintf(stderr,("Basic test on add_mirror failed\n"));
           rep= false;
           
           }
     delete_game(jeu);
     return rep;

}
bool test_set_required_nb_seen(){
bool nb=true;
        game jeu= new_game();
        assert(jeu);
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

if((required_nb_seen(jeu, N, 0)!=0 )|| (required_nb_seen(jeu, N, 1)!=3) ||(required_nb_seen(jeu, N, 2)!=3 )|| (required_nb_seen(jeu, N, 3)!=0)){
	fprintf(stderr,"le test de  base sur set_required_nb_seen  a echoué cote NORD\n");
          	nb= false;
	}
else if ((required_nb_seen(jeu, S, 0)!=0)||(required_nb_seen(jeu, S, 1)!=3) ||(required_nb_seen(jeu, S, 2)!=2 )||(required_nb_seen(jeu, S, 3)!=3)){
	fprintf(stderr,"le test de  base sur set_required_nb_seen  a echoué cote SUD\n");
          	nb= false;
	}
else if ((required_nb_seen(jeu, W, 3)!=3) ||(required_nb_seen(jeu, W, 2)!=3 )||(required_nb_seen(jeu, W, 1)!=2) || (required_nb_seen(jeu, W, 0)!=0)){
	fprintf(stderr,"le test de  base sur set_required_nb_seen  a echoué cote OUEST\n");
          	nb= false;
	}
else if ((required_nb_seen(jeu, E, 3)!=2) ||(required_nb_seen(jeu, E, 2)!=3) ||(required_nb_seen(jeu, E, 1)!=0) ||(required_nb_seen(jeu, E, 0)!=0)){
		fprintf(stderr,"le test de  base sur set_required_nb_seen  a echoué cote EST\n");
          	nb= false;
	}

	delete_game(jeu);
     	return nb;
      
 }

int main(void){
  bool result = true;
 result = test_set_required_nb_monster() && result;
  result = test_add_mirror() && result;
result = test_set_required_nb_seen() && result;
  if(result){
      printf("Tests successfull\n");
      return EXIT_SUCCESS;
  }
  else{
      printf("Tests failed\n");
      return EXIT_FAILURE;
  }
}


