#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts     

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "model.h"
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


