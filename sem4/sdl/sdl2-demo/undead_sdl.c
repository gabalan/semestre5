// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts     

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "model.h"

/* **************************************************************** */
     
struct Env_t {  
	SDL_Texture * vampire;
	SDL_Texture * zombie;
	SDL_Texture * ghost;
	SDL_Texture * spirit;
	SDL_Texture * text;
	int z_x,z_y;
	int v_x,v_y;
	int g_x,g_y;
	int s_x,s_z;
	int nb_s,nb_z,nb_v,nb_g;


}; 

/* **************************************************************** */
     
Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[])
{  
  Env * env = malloc(sizeof(struct Env_t));

  /* PUT YOUR CODE HERE TO INIT TEXTURES, ... */

  return env;
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
