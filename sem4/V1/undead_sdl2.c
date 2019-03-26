// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts

#include "game.h"
#include "game_io.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>
#include "model.h"



/* **************************************************************** */

#define FONT "Arial.ttf"
#define FONTSIZE 36
#define BACKGROUND "background.png"
#define ZOMBIES "zombie.png"
#define GHOSTS "ghost.png"
#define VAMPIRES "vampire.png"
#define SPIRITS "spirit.png"
#define POINTS "point.png"

/* **************************************************************** */

struct Env_t {
  SDL_Texture * background;
  SDL_Texture * zombie;
  SDL_Texture * ghost;
  SDL_Texture * vampire;
  SDL_Texture * spirits;
  SDL_Texture * point;
  SDL_Texture * textV;
  SDL_Texture * textG;
  SDL_Texture * textZ;
  SDL_Texture * textS;
  SDL_Texture * text;
  SDL_Texture * textR;
  SDL_Texture * textprincipe;
  SDL_Texture * textsolveur;
  int zombie_x, zombie_y;
  int ghost_x, ghost_y;
  int vampire_x, vampire_y;
  int spirit_x, spirit_y;
  int point_x, point_y;
  int i , j;
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
  env->zombie_x = 0;
  env->zombie_y = 0;
  env->vampire_x = 0;
  env->vampire_y = 0;
  env->ghost_x = 0;
  env -> ghost_y = 0;
  env-> spirit_x = 0;
  env->spirit_y = 0;
  env ->point_x = 0;
  env ->point_y = 0;
  env -> i = 0;
  env -> j = 0;
  env->g = load_game(argv[1]);

  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, BACKGROUND);
  if(!env->background) ERROR("IMG_LoadTexture: %s\n", BACKGROUND);

  /* init point texture from PNG image */
  env->point = IMG_LoadTexture(ren, POINTS);
  if(!env->point) ERROR("IMG_LoadTexture: %s\n", POINTS);


  /* init zombie texture from PNG image */
  env->zombie = IMG_LoadTexture(ren, ZOMBIES);
  if(!env->zombie) ERROR("IMG_LoadTexture: %s\n", ZOMBIES);

  /* init vampire texture from PNG image */
  env->vampire = IMG_LoadTexture(ren, VAMPIRES);
  if(!env->vampire) ERROR("IMG_LoadTexture: %s\n", VAMPIRES);

  /* init vampire texture from PNG image */
  env->ghost = IMG_LoadTexture(ren, GHOSTS);
  if(!env->ghost) ERROR("IMG_LoadTexture: %s\n", GHOSTS);

 /* init spirits texture from PNG image */
  env->spirits = IMG_LoadTexture(ren, SPIRITS);
  if(!env->spirits) ERROR("IMG_LoadTexture: %s\n", SPIRITS);

  /* init text texture using Arial font (Vampire)*/
  //int c = required_nb_monster(env->g,VAMPIRE);
  char b[50];
  sprintf(b,"%d",required_nb_monsters(env->g,VAMPIRE));
  SDL_Color color = { 255, 195, 51, 0 }; /* blue color in RGBA */
  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  SDL_Surface * surf = TTF_RenderText_Blended(font, b, color); // blended rendering for ultra nice text
  env->textV = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);

  /* init text texture using Arial font (GHOST)*/
  //int c = required_nb_monster(env->g,GHOST);

  sprintf(b,"%d",required_nb_monsters(env->g,GHOST));
  font = TTF_OpenFont(FONT, FONTSIZE);
  surf = TTF_RenderText_Blended(font, b, color); // blended rendering for ultra nice text
  env->textG = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);

  /* init text texture using Arial font (ZOMBIE)*/
  //int c = required_nb_monster(env->g,ZOMBIE);
  sprintf(b,"%d",required_nb_monsters(env->g,ZOMBIE));
  font = TTF_OpenFont(FONT, FONTSIZE);
  surf = TTF_RenderText_Blended(font, b, color); // blended rendering for ultra nice text
  env->textZ = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);


  /* init text texture using Arial font (SPIRIT)*/
  //int c = required_nb_monster(env->g,SPIRIT);
  sprintf(b,"%d",required_nb_monsters(env->g,SPIRIT));
  font = TTF_OpenFont(FONT, FONTSIZE);
  surf = TTF_RenderText_Blended(font, b, color); // blended rendering for ultra nice text
  env->textS = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);

  /* init text texture using Arial font (message de victoire)*/
  font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  surf = TTF_RenderText_Blended(font, "CONGRATULATION ,YOU WIN !", color); // blended rendering for ultra nice text
  env->text = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);

  /* init text texture using Arial font (Restart)*/
  font = TTF_OpenFont(FONT, 20);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  surf = TTF_RenderText_Blended(font, "Restart ", color); // blended rendering for ultra nice text
  env->textR = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);

  /* init text texture using Arial font (textsolveur)*/
  font = TTF_OpenFont(FONT, 20);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  surf = TTF_RenderText_Blended(font, "solveur ", color); // blended rendering for ultra nice text
  env->textsolveur = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);




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
  int height = game_height(env->g);
  int width = game_width(env->g);

  /* define constant  */
  int y1 = 6*h/(2*height+8);
  int y2 = (2*height+6)*h/(2*height+8);
  int x1 = 2*w/(2*width+4);
  int x2 = (2*width+2)*w/(2*width+4);
  char b[50];
  SDL_Color color = { 255, 192, 51, 0 }; /* blue color in RGBA */
  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  SDL_Surface * surf = TTF_RenderText_Blended(font, b, color); // blended rendering for ultra nice text


  /* render background texture */
  SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */

  /* render Restart texture */
  SDL_QueryTexture(env->textR, NULL, NULL, &rect.w, &rect.h);
  rect.x = 50; rect.y = 100;
  SDL_RenderCopy(ren, env->textR, NULL, &rect);
  /* render Restart solveur */
  SDL_QueryTexture(env->textsolveur, NULL, NULL, &rect.w, &rect.h);
  rect.x = 200; rect.y = 100;
  SDL_RenderCopy(ren, env->textsolveur, NULL, &rect);



  /* render point texture */
  SDL_QueryTexture(env->point, NULL, NULL, &rect.w, &rect.h);
  rect.x = env->point_x + (x1 + ((x2-x1)/height)/2); rect.y = env -> point_y + (y2 + ((y1-y2)/height)/2);
  SDL_RenderCopy(ren, env->point, NULL, &rect);

  /* render zombie texture */
  SDL_QueryTexture(env->zombie, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/4; rect.y = 23;
  SDL_RenderCopy(ren, env->zombie, NULL, &rect);

  /* render vampire texture */
  SDL_QueryTexture(env->vampire, NULL, NULL, &rect.w, &rect.h);
  rect.x = 2*(w/4); rect.y = 23;
  SDL_RenderCopy(ren, env->vampire, NULL, &rect);


  /* render ghost texture */
  SDL_QueryTexture(env->ghost, NULL, NULL, &rect.w, &rect.h);
  rect.x = 3*(w/4); rect.y = 23;
  SDL_RenderCopy(ren, env->ghost, NULL, &rect);

  /* render spirits texture */
  SDL_QueryTexture(env->spirits, NULL, NULL, &rect.w, &rect.h);
  rect.x = 50; rect.y = 23;
  SDL_RenderCopy(ren, env->spirits, NULL, &rect);

  /* render text texture vampire */
  SDL_QueryTexture(env->textV, NULL, NULL, &rect.w, &rect.h);
  rect.x = (2*(w/4))+100; rect.y = 23;
  SDL_RenderCopy(ren, env->textV, NULL, &rect);

  /* render text texture ghost */
  SDL_QueryTexture(env->textG, NULL, NULL, &rect.w, &rect.h);
  rect.x = (3*(w/4))+100; rect.y = 23;
  SDL_RenderCopy(ren, env->textG, NULL, &rect);


  /* render text texture zombie */
  SDL_QueryTexture(env->textZ, NULL, NULL, &rect.w, &rect.h);
  rect.x = ((w/4))+100; rect.y = 23;
  SDL_RenderCopy(ren, env->textZ, NULL, &rect);


  /* render text texture spirit */
  SDL_QueryTexture(env->textS, NULL, NULL, &rect.w, &rect.h);
  rect.x = 120; rect.y = 23;
  SDL_RenderCopy(ren, env->textS, NULL, &rect);


  /* render grille texture */
  SDL_SetRenderDrawColor(ren, 255, 154, 98, SDL_ALPHA_OPAQUE);
  for (int x = 0; x <= width ; x++){
    SDL_RenderDrawLine(ren, (2*x+2)*w/(2*width+4), 6*h/(2*height+8), (2*x+2)*w/(2*width+4),(2*height+6)*h/(2*height+8));
  }
  for(int y =0;y<=height;y++){
    SDL_RenderDrawLine(ren,2*w/(2*width+4), (2*y+6)*h/(2*height+8),(2*width+2)*w/(2*width+4),(2*y+6)*h/(2*height+8));
  }
  /* render required_nb_seen EST texture */
  for(int i = 0 ; i < height ; i++){
    sprintf(b,"%d",required_nb_seen(env->g,E,i));
    font = TTF_OpenFont(FONT, FONTSIZE);
    surf = TTF_RenderText_Blended(font, b, color); // blended rendering for ultra nice text
    TTF_CloseFont(font);

    SDL_QueryTexture(SDL_CreateTextureFromSurface(ren, surf), NULL, NULL, &rect.w, &rect.h);
    rect.x = x1-50; rect.y = (y1 + ((y2-y1)/height)/2) + ((y2-y1)/4)*i ;
    SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, surf), NULL, &rect);
  }

  /* render required_nb_seen NORD texture */
  for(int i = 0 ; i < width ; i++){
    sprintf(b,"%d",required_nb_seen(env->g,N,i));
    font = TTF_OpenFont(FONT, FONTSIZE);
    surf = TTF_RenderText_Blended(font, b, color); // blended rendering for ultra nice text
    TTF_CloseFont(font);

    SDL_QueryTexture(SDL_CreateTextureFromSurface(ren, surf), NULL, NULL, &rect.w, &rect.h);
    rect.x = (x1 + ((x2-x1)/height)/2) + ((x2-x1)/4)*i; rect.y = y1 - 50 ;
    SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, surf), NULL, &rect);
  }

  /* render required_nb_seen SUD texture */
  for(int i = 0 ; i < width ; i++){
    sprintf(b,"%d",required_nb_seen(env->g,S,i));
    font = TTF_OpenFont(FONT, FONTSIZE);
    surf = TTF_RenderText_Blended(font, b, color); // blended rendering for ultra nice text
    TTF_CloseFont(font);

    SDL_QueryTexture(SDL_CreateTextureFromSurface(ren, surf), NULL, NULL, &rect.w, &rect.h);
    rect.x = (x1 + ((x2-x1)/height)/2) + ((x2-x1)/4)*i; rect.y = y2 ;
    SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, surf), NULL, &rect);
  }
  /* render required_nb_seen OUEST texture */
  for(int i = 0 ; i < height ; i++){
    sprintf(b,"%d",required_nb_seen(env->g,W,i));
    font = TTF_OpenFont(FONT, FONTSIZE);
    surf = TTF_RenderText_Blended(font, b, color); // blended rendering for ultra nice text
    TTF_CloseFont(font);

    SDL_QueryTexture(SDL_CreateTextureFromSurface(ren, surf), NULL, NULL, &rect.w, &rect.h);
    rect.x = x2+20; rect.y = (y1 + ((y2-y1)/height)/2) + ((y2-y1)/4)*i ;
    SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, surf), NULL, &rect);
  }
  /*render monsters texture */
  for(int i = height -1; i >= 0; i--){
    for(int j = 0; j < width; j++){
      content contenu=get_content(env -> g,j,i);
      switch (contenu) {
        case  MIRROR:
        font = TTF_OpenFont(FONT, FONTSIZE);
        surf = TTF_RenderText_Blended(font, "/", color);
        TTF_CloseFont(font);
        SDL_QueryTexture(SDL_CreateTextureFromSurface(ren, surf), NULL, NULL, &rect.w, &rect.h);
        rect.x = ((x1 + ((x2-x1)/height)/2) + ((x2-x1)/4)*j) -30; rect.y = ((y2 + ((y1-y2)/height)/2) + ((y1-y2)/4)*i) -30 ;
        SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, surf), NULL, &rect);
        break;

        case  ANTIMIRROR:
        font = TTF_OpenFont(FONT, FONTSIZE);
        surf = TTF_RenderText_Blended(font, "\\", color);
        TTF_CloseFont(font);
        SDL_QueryTexture(SDL_CreateTextureFromSurface(ren, surf), NULL, NULL, &rect.w, &rect.h);
        rect.x = ((x1 + ((x2-x1)/height)/2) + ((x2-x1)/4)*j) - 30; rect.y = ((y2 + ((y1-y2)/height)/2) + ((y1-y2)/4)*i) -30 ;
        SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, surf), NULL, &rect);
        break;

        case  VMIRROR:
        font = TTF_OpenFont(FONT, FONTSIZE);
        surf = TTF_RenderText_Blended(font, "|", color);
        TTF_CloseFont(font);
        SDL_QueryTexture(SDL_CreateTextureFromSurface(ren, surf), NULL, NULL, &rect.w, &rect.h);
        rect.x = ((x1 + ((x2-x1)/height)/2) + ((x2-x1)/4)*j) - 20; rect.y = ((y2 + ((y1-y2)/height)/2) + ((y1-y2)/4)*i) -30 ;
        SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, surf), NULL, &rect);
        break;

        case  HMIRROR:
        font = TTF_OpenFont(FONT, FONTSIZE);
        surf = TTF_RenderText_Blended(font, " - ", color);
        TTF_CloseFont(font);
        SDL_QueryTexture(SDL_CreateTextureFromSurface(ren, surf), NULL, NULL, &rect.w, &rect.h);
        rect.x = ((x1 + ((x2-x1)/height)/2) + ((x2-x1)/4)*j) -20 ; rect.y = ((y2 + ((y1-y2)/height)/2) + ((y1-y2)/4)*i) -30 ;
        SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, surf), NULL, &rect);
        break;

        case  VAMPIRE:
        font = TTF_OpenFont(FONT, FONTSIZE);
        surf = TTF_RenderText_Blended(font, VAMPIRES, color);
        TTF_CloseFont(font);
        SDL_QueryTexture(env->vampire, NULL, NULL, &rect.w, &rect.h);
        rect.x = ((x1 + ((x2-x1)/height)/2) + ((x2-x1)/4)*j) - 30; rect.y = ((y2 + ((y1-y2)/height)/2) + ((y1-y2)/4)*i) - 30 ;
        SDL_RenderCopy(ren, env->vampire,NULL, &rect);
        break;

        case  GHOST:
        font = TTF_OpenFont(FONT, FONTSIZE);
        surf = TTF_RenderText_Blended(font, GHOSTS, color);
        TTF_CloseFont(font);

        SDL_QueryTexture(env->ghost, NULL, NULL, &rect.w, &rect.h);
        rect.x = ((x1 + ((x2-x1)/height)/2) + ((x2-x1)/4)*j) - 30; rect.y = ((y2 + ((y1-y2)/height)/2) + ((y1-y2)/4)*i) - 30 ;
        SDL_RenderCopy(ren, env->ghost, NULL, &rect);
        break;

        case  ZOMBIE:
        font = TTF_OpenFont(FONT, FONTSIZE);
        surf = TTF_RenderText_Blended(font, ZOMBIES, color);
        TTF_CloseFont(font);
        SDL_QueryTexture(env->zombie, NULL, NULL, &rect.w, &rect.h);
        rect.x = ((x1 + ((x2-x1)/height)/2) + ((x2-x1)/4)*j) - 30; rect.y = ((y2 + ((y1-y2)/height)/2) + ((y1-y2)/4)*i) - 30 ;
        SDL_RenderCopy(ren, env->zombie,NULL, &rect);
        break;

        case  SPIRIT:
        font = TTF_OpenFont(FONT, FONTSIZE);
        surf = TTF_RenderText_Blended(font, SPIRITS, color);
        TTF_CloseFont(font);
        SDL_QueryTexture(env->spirits, NULL, NULL, &rect.w, &rect.h);
        rect.x = ((x1 + ((x2-x1)/height)/2) + ((x2-x1)/4)*j) - 30; rect.y = ((y2 + ((y1-y2)/height)/2) + ((y1-y2)/4)*i) - 30 ;
        SDL_RenderCopy(ren, env->spirits,NULL, &rect);
        break;

        case EMPTY:
        font = TTF_OpenFont(FONT, FONTSIZE);
        surf = TTF_RenderText_Blended(font, "  ", color);
        TTF_CloseFont(font);
        SDL_QueryTexture(SDL_CreateTextureFromSurface(ren, surf), NULL, NULL, &rect.w, &rect.h);
        rect.x = (x1 + ((x2-x1)/height)/2) + ((x2-x1)/4)*j; rect.y = (y2 + ((y1-y2)/height)/2) + ((y1-y2)/4)*i ;
        SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, surf), NULL, &rect);
        break;
      }
    }
  }

if (is_game_over(env -> g)){
  /* render text texture */
  SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
  rect.x = w/2 - rect.w/2; rect.y = h/2 - rect.h/2;
  SDL_RenderCopy(ren, env->text, NULL, &rect);
}


}

/* **************************************************************** */


bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e)
{
  int w, h;
  SDL_GetWindowSize(win, &w, &h);




  int height = game_height(env->g);
  int width = game_width(env->g);
  int y1 = 6*h/(2*height+8);
  int y2 = (2*height+6)*h/(2*height+8);
  int x1 = 2*w/(2*width+4);
  int x2 = (2*width+2)*w/(2*width+4);

  int *pi = &(env->i);
  int *pj = &(env->j);

  /* generic events */
  if (e->type == SDL_QUIT) {
    return true;
  }

  else if (e->type == SDL_MOUSEBUTTONDOWN) {
    SDL_Point mouse;
     SDL_GetMouseState(&mouse.x, &mouse.y);
     int a=mouse.x;
     int b=mouse.y;
       printf("Appui :%d %d\n", a,b);
       //bouton pour reprendre le jeu
    if ((a>=40 && a<=138) && (b>=97 && b <= 123)){
      restart_game(env -> g);
    }
    else   if ((a>=192 && a<=291) && (b>=97 && b <= 123)){
      sol_recursive(env->g,0,false);
    }
  }

  else if (e->type == SDL_KEYDOWN) {
    switch (e->key.keysym.sym) {

      /*AJOUT D'UN ZOMBIES*/
      case SDLK_z:
      add_monster(env->g, ZOMBIE, *pi,*pj);
      break;
      /*AJOUT D'UN ZOMBIES*/
      case SDLK_g:
      add_monster(env->g, GHOST, *pi,*pj);
      break;
      /*AJOUT D'UN VAMPIRE*/
      case SDLK_v:
      add_monster(env->g, VAMPIRE, *pi,*pj);
      break;
      /*AJOUT D'UN SPIRIT*/
      case SDLK_s:
      add_monster(env->g, SPIRIT, *pi,*pj);
      break;

      /*LA TOUCHE GAUCHE DU CLAVIER POUR SE DIRIGER A GAUCHE*/
      case SDLK_LEFT:
      env->point_x -= ((x2-x1)/4);
      *pi = *pi-1;
      break;

      /*LA TOUCHE DROITE DU CLAVIER POUR SE DIRIGER A DROITE*/
      case SDLK_RIGHT:
      env->point_x += ((x2-x1)/4);
      *pi = *pi+1;
      break;

      /*LA TOUCHE HAUT DU CLAVIER POUR MONTER*/
      case SDLK_UP:
      env->point_y -= ((y2-y1)/4);
      *pj = *pj+ 1;
      break;

      /*LA TOUCHE BAS POUR DESCENDRE*/
      case SDLK_DOWN:
      env->point_y += ((y2-y1)/4);
      *pj = *pj - 1;
      break;

      /*LA TOUCHE ECHAP POUR SORTIR */
      case SDLK_ESCAPE:  return true; break;
    }
  }

  /* PUT YOUR CODE HERE TO PROCESS EVENTS */
  return false;
}


/* **************************************************************** */


void clean(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */
  SDL_DestroyTexture(env->background);
  SDL_DestroyTexture(env->zombie);
  SDL_DestroyTexture(env->ghost);
  SDL_DestroyTexture(env->vampire);
  SDL_DestroyTexture(env->spirits);
  SDL_DestroyTexture(env->point);
  SDL_DestroyTexture(env->textV);
  SDL_DestroyTexture(env->textG);
  SDL_DestroyTexture(env->textZ);
  SDL_DestroyTexture(env->textS);
  SDL_DestroyTexture(env->text);
  delete_game(env -> g);

  free(env);
}

/* **************************************************************** */
