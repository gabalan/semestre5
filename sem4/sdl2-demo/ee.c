#include<SDL2/SDL.h>
#include<stdio.h>
const int WIDTH  = 640;
const int HEIGHT = 480;
 
int main(int argc, char** argv)
{
  SDL_Window *win = 0;
  SDL_Renderer *ren = 0;
 
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
  SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
  SDL_RenderClear(ren);
  SDL_RenderPresent(ren);
 
  SDL_Delay(4000);
 
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
return 0;
}
