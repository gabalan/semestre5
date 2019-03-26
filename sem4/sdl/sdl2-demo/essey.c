SDL_Rect r;
//...
 
r.w=50;
r.h=50;
for (i=0; i< nbcase; i ++) {
        SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
        for (j=0; j< nbcase; j ++) {
                r.x=50 + i*50;
                r.y=50 + j*50;
                SDL_RenderDrawRect(ren,&r);
                SDL_RenderPresent(ren);
        }
  
    }
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

}; 
//La transparence est activée

SDL_Surface* surface = NULL;
Uint32 rmask, gmask, bmask, amask; // Déclaration des masks

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
if(surface == NULL)
{
    printf("Erreur lors de la creation de la surface : %s", SDL_GetError());
    return EXIT_FAILURE;
}
     
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
