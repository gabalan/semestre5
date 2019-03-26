#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL_phelma.h>


/*
	Cette fonction permet de gerer le clavier et la souris
*/
int gestionclavier() { SDL_Event event;
	/* On attend un evenement, qui peut etre tapez sur le clavier, bouger la souris, etc...
           Si on ne fait rien, le programme reste bloque ici.
	   Si on ne veut pas attendre, comme dans un jeu, on utilise SDL_PollEvent
	*/
   SDL_WaitEvent(&event); /* SDL_PollEvent(&event);*/
	/* On recupere cet evenement et on le traite en fonction de sa nature.
	   Ici, on affiche un truc, pas tres utile, mais pedagogique
 	   En general, on utilise ces informations ensuite pour faire qqchose dans la fonction qui appelle le gestionnaire
	*/
   switch(event.type) {
      case SDL_QUIT: return 0;
	/* Ca, ce sont les evenements de type : on appui sur une touche */
      case SDL_KEYDOWN :
        switch(event.key.keysym.sym) {
          case SDLK_UP : printf("Touche haut \n"); return 1;
          case SDLK_DOWN : printf("Touche bas\n"); return 2;
          case SDLK_LEFT: printf("Touche gauche\n"); return 3;
          case SDLK_RIGHT : printf("Touche droite\n"); return 4;
          case SDLK_ESCAPE : printf("Touche  ESC\n"); return 5;
          case SDLK_KP1 : printf("Touche 1\n"); return '1';
          case SDLK_KP2 : printf("Touche 2\n"); return '2';
          case SDLK_KP3 : printf("Touche 3\n"); return '3';
          case SDLK_KP4 : printf("Touche 4\n"); return '4';
        };
        printf("Une touche appuyÃ©e, mais pas la bonne\n");
        return -1;

	/* La, on bouge la souris et on affiche la nouvelle position  : attention, ca en fait beaucoup */
      case SDL_MOUSEMOTION: printf("Souris en position %d %d\n",event.motion.x, event.motion.y); break;

	/* La, on clic sur la souris */
      case SDL_MOUSEBUTTONDOWN:
        switch (event.button.button) {
           case SDL_BUTTON_RIGHT : printf("Clic droit\n"); break;
           case SDL_BUTTON_LEFT : printf("Clic gauche\n"); break;
           case SDL_BUTTON_MIDDLE : printf("Clic Centre\n"); break;
        }
   }
   return -2;
}


int main(int argc, char *argv[])
{   SDL_Surface* fenetre,* objet[4];;
    SDL_Rect posobjet1, posobjet2;
    int rep,dimx=400, dimy=300;

    printf("Ce programme teste la gestion diu clavier et de la souris avec la SDL. Il affiche Mario dans fenetre. Les fleches haut,bas,droite,gauche l'affiche de profil de face ou de dos selon le cas. Tapez ESC pour quitter\n");

        /* Creation d'une fenetre de dimension dimx x dimy, couleurs sur 32 bits */
    fenetre = newfenetregraphique(dimx, dimy);
        /* Cette fenetre est remplie par un rectangle de couleur verdatre (R=17, V=206, B=112),
           chaque couleur pirmaire pouvnat aller de 0 Ã  255 */
    SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 0, 128, 64));

        /* Auto repeat du clavier */
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

        /* Chargement des images de Mario dans des objets de types SDL_Surface
           objet[0] correspond a Mario de dos, objet[1] correspond a Mario de face
	   objet[3] correspond a Mario vers la gauche, objet[2] correspond a Mario vers la droite
	  On peut lire de nombreux fichiers images sans problemes
	 */
    objet[0]=IMG_Load("mario_bas.gif");  if( objet[0]==NULL) { printf("FIchier mario_bas.gif non present\n"); exit(1);}
    objet[1]=IMG_Load("mario_haut.gif"); if( objet[1]==NULL) { printf("FIchier mario_haut.gif non present\n"); exit(1);}
    objet[2]=IMG_Load("mario_gauche.gif"); if( objet[2]==NULL) { printf("FIchier mario_gauche.gif non present\n"); exit(1);}
    objet[3]=IMG_Load("mario_droite.gif"); if( objet[3]==NULL) { printf("FIchier mario_droite.gif non present\n"); exit(1);}

	/* La position ou sera afichee l'image de Mario */
    posobjet1.x=50; posobjet1.y=150;
    rep=1;
	/* La boule de traitement : on affiche l'image de Mario correspondant a l'etat de la variable rep,
	  qui depend des touches tapees : fleches haut, bas, gauche, droite
	*/
    do {
      if (rep>=1 && rep<=4) {
		/* On met a jour la fenetre en redessinant le bon mario */
           SDL_BlitSurface(objet[rep-1], NULL, fenetre, &posobjet1);
      }
		/* On affiche la fenetre a l'ecran */
      SDL_Flip(fenetre); // Mise Ã  jour de l'Ã©cran
	/* On teste si un touche clavier est frappee et laquelle
	   rep contient le code que nous avons defini
        */
      rep=gestionclavier();
    } while(rep!=5 && rep!=0);

	/* Pour quitter proprement, on libere le fenetre et les objets */
    SDL_FreeSurface(fenetre);
    SDL_FreeSurface(objet[0]); SDL_FreeSurface(objet[1]);
    SDL_FreeSurface(objet[2]); SDL_FreeSurface(objet[3]);
    SDL_Quit();

    return EXIT_SUCCESS;
}
