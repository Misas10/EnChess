#ifndef LOAD_H
#define LOAD_H

#include "definitons.h"

void svg2Tex() {
  /*SDL_RWops *rw = SDL_RWFromFile("src/assets/light.svg", "r");*/
  /*if(rw == NULL)*/
  /*  printf("\nError Trying opening the file: %s\n", SDL_GetError());*/
  /**/
  /*SDL_Surface *surface = IMG_LoadSVG_RW(rw);*/
  /**/
  /*if(surface == NULL)*/
  /*  printf("\nError Trying to convert image to surface: %s\n", SDL_GetError());*/

  SDL_Texture *texture = IMG_LoadTexture(Game.screen.renderer, "src/assets/light.svg");
  if(texture == NULL)
    printf("\nError Trying to convert image to texture: %s\n", SDL_GetError());

  SDL_Rect texture_rect;
  texture_rect.x = Game.screen.w / 2 - Game.screen.w / 4 ; //the x coordinate
  texture_rect.y = Game.screen.h / 2 - Game.screen.h / 4; //the y coordinate
  texture_rect.w = 500; //the width of the texture
  texture_rect.h = 500; //the height of the texture

  SDL_RenderClear(Game.screen.renderer); //clears the renderer
  SDL_RenderCopy(Game.screen.renderer, texture, NULL, &texture_rect); 
  SDL_RenderPresent(Game.screen.renderer);
}

#endif // !LOAD_H
