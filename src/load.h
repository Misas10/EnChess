#ifndef LOAD_H
#define LOAD_H

#include "definitons.h"

Image svg2Tex(char *fileName, int width, int height) {

  // Create RAW svg data
  SDL_RWops *rw = SDL_RWFromFile(fileName, "r");
  if(rw == NULL)
    printf("\nError Trying opening the SVG: %s\n", SDL_GetError());

  // Scale SVG with the defined width and height
  SDL_Surface *surface = IMG_LoadSizedSVG_RW(rw, width, height);
  if(surface == NULL)
    printf("\nError Trying to convert image to surface: %s\n", SDL_GetError());

  SDL_Texture *tex = SDL_CreateTextureFromSurface(Game.screen.renderer, surface);
  if(tex == NULL)
    printf("\nError Trying to convert SVG to texture: %s\n", SDL_GetError());

  Image image = {
    tex,
    width,
    height
  };

  SDL_FreeSurface(surface);

  return image;
}

#endif // !LOAD_H
