// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts     

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "model.h"
const int WIDTH  = 640;
const int HEIGHT = 480;
/* **************************************************************** */
     
struct Env_t {  

 
};
     
/* **************************************************************** */
     
Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[])
{  
  Env * env = malloc(sizeof(struct Env_t));

  /* Initialisation de la SDL. Si ça se passe mal, on quitte */
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
      fprintf(stderr,"Erreur initialisation\n");
      return -1;
  }
  /* Création de la fenêtre et du renderer */
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren); // SDL_WINDOW_SHOWN|SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,&win,&ren);
 
  if (!win || !ren) 
	 {
		fprintf(stderr,"Erreur à la création des fenêtres\n");
		SDL_Quit();
		return -1;
	 }
  /* Affichage du fond noir */
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  SDL_RenderClear(ren);
  SDL_RenderPresent(ren);
DL_Delay(400000000000000); 
dessin(ren) ;
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
return 0;

  
//  return env;
}
   void dessin(SDL_Renderer * ren) 
{
  int colr, colg, colb;
  SDL_Rect r;
  int i;
 
  SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_BLEND);
  for(i=0;i<30;i++) 
	 {
		r.x = rand()%WIDTH;
		r.y = rand()%HEIGHT;
		r.w = rand()%(WIDTH-r.x);
		r.h = rand()%(HEIGHT-r.y);
		colr = rand()%256;
		colg = rand()%256;
		colb = rand()%256;
		SDL_SetRenderDrawColor(ren,colr,colg,colb,20);
		SDL_RenderFillRect(ren,&r);
	 }
  SDL_RenderPresent(ren);
}  
/* **************************************************************** */
     
void render(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
}
     
/* **************************************************************** */
     
     
bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e)
{     

  if (e->type == SDL_QUIT) {
    return true;
  }

  /* PUT YOUR CODE HERE TO PROCESS EVENTS */
  
  return false; 
}

/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */

  free(env);
}
     
/* **************************************************************** */
