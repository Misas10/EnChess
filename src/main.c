
#include "definitons.h"
#include "lifecycle.h"
#include "render.h"
#include "load.h"
#include "events.h"
#include <stdio.h>

int main() {
  Game.init();

  /*SDL_AddEventWatch(resizingEventWatcher, Game.screen.window);*/
  loadTextures();

  SDL_Event event;

  while(Game.isRunning) {

    if(SDL_WaitEvent(&event)){
      switch (event.type) { 
        case SDL_QUIT:
          Game.isRunning = false;
          break;

        case SDL_KEYDOWN:
          if(event.key.keysym.sym  == SDLK_q) {
            printf("'q' Key pressed, exiting the game\n");
            Game.isRunning = false;
          }

          if(event.key.keysym.sym  == SDLK_i)
            gameData.isReversed = !gameData.isReversed;

          break;
      }
    }

    render();
    /*SDL_*/

  }
  Game.quit();

  return 0;
}
