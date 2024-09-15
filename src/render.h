#ifndef RENDER_H

#define RENDER_H
#include "definitons.h"
#include <SDL2/SDL_render.h>

void render() {
  printf("render\n");
  /*SDL_SetRenderDrawColor(Game.screen.renderer, 255, 255, 255, 255);*/
  /*if(Game.screen.window == NULL) {*/
  /*  printf("Failed to create window: %s", SDL_GetError());*/
  /*  Game.isRunning = SDL_FALSE;*/
  /*  return;*/
  /*}*/

  /*SDL_RenderClear(Game.screen.renderer);*/
  SDL_RenderPresent(Game.screen.renderer);
}

#endif

