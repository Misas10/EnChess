
#include "../include/bitboard.h"
#include "../include/definitons.h"
#include "../include/events.h"
#include "../include/lifecycle.h"
#include "../include/load.h"
#include "../include/render.h"

int main() {
  Game.init();

  loadTextures();

  SDL_Event event;

  while (Game.isRunning) {

    if (SDL_WaitEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        Game.isRunning = false;
        break;

      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_q) {
          printf("'q' Key pressed, exiting the game\n");
          Game.isRunning = false;
        }

        if (event.key.keysym.sym == SDLK_i)
          gameData.isReversed = !gameData.isReversed;

        break;

      case SDL_MOUSEBUTTONDOWN:
        mouseClick(event.button);
        break;
      }
    }

    render();
    /*SDL_*/
  }
  Game.quit();

  return 0;
}
