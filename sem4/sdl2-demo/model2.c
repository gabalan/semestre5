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

  /* PUT YOUR VARIABLES HERE */

  SDL_Texture * zombie;
  SDL_Texture * vamppire;
  SDL_Texture * spirits;  
  SDL_Texture * ghost;
  SDL_Texture * nb_z;
  SDL_Texture * nb_v;
  SDL_Texture * nb_s;
  SDL_Texture * nb_g;
  int x_z, y_z;
  int x_s, y_s;
  int x_g, y_g;
  int x_v, y_v;  
};
     
/* **************************************************************** */
     
Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[])
{  
  Env * env = malloc(sizeof(struct Env_t));

  PRINT("Move the bomb with keyboard arrows and move Mario with mouse.\n");
  PRINT("Press ESC to quit. Enjoy this SDL2 sample!\n"); 
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* init positions */
  env->bomb_x = w/2;
  env->bomb_y = h/4;
  env->mario_x = w/2;
  env->mario_y = 3*h/4;
  
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
