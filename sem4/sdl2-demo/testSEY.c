#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "game.h"
#include"game_io.h"



bool testnewgame(){
	game g = new_game();
   	assert(g);

	bool res = true;
	for (int i=3; i>=0; i--){
		for(int j=0;j<4;j++){
			if(get_content(g, j, i)!=EMPTY){
				res = false;
				fprintf(stderr,("Error newgame didn't work\n"));
                                delete_game (g);
				return res;
				}
		}
	}
       delete_game (g);
	return res;
}

bool test_restart_game(){
   	bool res = true;
	game jeu = new_game();

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

        add_mirror(jeu, 1, 0, 3);
        add_mirror(jeu, 0, 3, 3);
        add_mirror(jeu, 1, 0, 2);
        add_mirror(jeu, 1, 2, 1);
        add_mirror(jeu, 0, 3, 1);
        add_mirror(jeu, 1, 0, 0);
        add_mirror(jeu, 1, 3, 0);

	restart_game(jeu);

	if(((get_content(jeu, 0, 1) == EMPTY)&& (get_content(jeu, 1, 0) == EMPTY) && (get_content(jeu, 2, 0) == EMPTY) && (get_content(jeu, 1, 1) == EMPTY)&&(get_content(jeu, 1,2 ) == EMPTY) && (get_content(jeu, 2,2 ) == EMPTY) &&(get_content(jeu, 2,3 ) == EMPTY) && (get_content(jeu, 1,3 ) == EMPTY) && (get_content(jeu, 3,2 ) == EMPTY)) && ((get_content(jeu,0,3)==ANTIMIRROR) && (get_content(jeu,3,3)==MIRROR) && (get_content(jeu,0,2)==ANTIMIRROR) &&(get_content(jeu,2,1)==ANTIMIRROR) && (get_content(jeu,3,1)==MIRROR) && (get_content(jeu,0,0)==ANTIMIRROR) && (get_content(jeu,3,0)==ANTIMIRROR))){
	  delete_game (jeu);
           return res;
	}
        delete_game (jeu);
	fprintf(stderr,("Error restart_game didn't work\n"));
	return false;
}

bool test_current_nbmonster(){
	bool res = true;
	game jeu = new_game();
	add_monster(jeu,ZOMBIE,0,1);
	add_monster(jeu,ZOMBIE,1,0);
	if (current_nb_monsters( jeu , ZOMBIE) != 2) {
		res = false;
		fprintf(stderr,("Error current_nb_monster didn't work\n"));
		delete_game (jeu);
		return res;
	}
	delete_game (jeu);
	return res;
}

bool test_current_nbseen(){
	bool res = true;
	game jeu = new_game();
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

	if (current_nb_seen( jeu , N , 1) != 3) {
		res = false;
		fprintf(stderr,("Error current_nb_seen didn't work\n"));
		delete_game (jeu);
		return res;
	}
	delete_game (jeu);
	return res;
}


int main(void){
	bool result = true;
  	result = testnewgame()&& result;
        result = test_restart_game() && result;
	result = test_current_nbmonster() && result;
	result = test_current_nbseen() && result;
  	if(result){
      		printf("Tests successfull\n");
      		return EXIT_SUCCESS;
  	}
  	else{
      		printf("Tests failed\n");
      		return EXIT_FAILURE;
  	}
}
