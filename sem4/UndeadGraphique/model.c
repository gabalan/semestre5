// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "model.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "model.h"
#include"game.h"
#include"game_io.h"

/* **************************************************************** */

#define FONT "Arial.ttf"
#define FONTSIZE 36
#define BACKGROUND "background.png"
#define ZOMBIE "zombie.png"
#define GHOST "ghost.png"
#define VAMPIRE "vampire.png"
#define SPIRIT "spirit.png"

/* **************************************************************** */

struct Env_t {
  SDL_Texture * background;
  SDL_Texture * zombie;
  SDL_Texture * ghost;
  SDL_Texture * vampire;
  SDL_Texture * spirits;
  int zombie_x, zombie_y;
  int ghost_x, ghost_y;
  int vampire_x, vampire_y;
  int spirit_x, spirit_y;
  game g;

  /* PUT YOUR VARIABLES HERE */

};

/* **************************************************************** */

Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[])
{
  Env * env = malloc(sizeof(struct Env_t));
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* init positions */
  env->zombie_x = w/2;
  env->zombie_y = h/4;
  env->vampire_x = w/2;
  env->vampire_y = 3*h/4;

  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, BACKGROUND);
  if(!env->background) ERROR("IMG_LoadTexture: %s\n", BACKGROUND);

  /* init mario texture from PNG image */
  env->zombie = IMG_LoadTexture(ren, ZOMBIE);
  if(!env->zombie) ERROR("IMG_LoadTexture: %s\n", ZOMBIE);

  /* init bomb texture from PNG image */
  env->vampire = IMG_LoadTexture(ren, VAMPIRE);
  if(!env->vampire) ERROR("IMG_LoadTexture: %s\n", VAMPIRE);


  /* PUT YOUR CODE HERE TO INIT TEXTURES, ... */

  return env;
}

/* **************************************************************** */

void render(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  SDL_Rect rect;
  /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* render background texture */
  SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */

  /* render zombie texture */
  SDL_QueryTexture(env->zombie, NULL, NULL, &rect.w, &rect.h);
  rect.x = 23; rect.y = 23;
  SDL_RenderCopy(ren, env->zombie, NULL, &rect);

  /* render vampire texture */
  SDL_QueryTexture(env->vampire, NULL, NULL, &rect.w, &rect.h);
  rect.x = 75; rect.y = 23;
  SDL_RenderCopy(ren, env->vampire, NULL, &rect);






  SDL_SetRenderDrawColor(ren, 254, 0, 0, SDL_ALPHA_OPAQUE); /* red */
  SDL_RenderDrawLine(ren, 50, 102, 102, 520);
  SDL_RenderDrawLine(ren, 101, 103, 518, 103);
  SDL_RenderDrawLine(ren, 519, 102, 519, 519);
  SDL_RenderDrawLine(ren, 102, 519, 519, 518);

  SDL_RenderDrawLine(ren, 206, 103, 206, 519);
  SDL_RenderDrawLine(ren, 309, 103, 309, 519);
  SDL_RenderDrawLine(ren, 412, 103, 412, 519);

  SDL_RenderDrawLine(ren, 102, 207, 518, 207);
  SDL_RenderDrawLine(ren, 102, 311, 518, 311);
  SDL_RenderDrawLine(ren, 102, 415, 518, 415);

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
