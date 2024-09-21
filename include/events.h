#ifndef EVENTS_H
#define EVENTS_H

#include "definitons.h"

void mouseClick(SDL_MouseButtonEvent mouse) {

  int x = mouse.x / lightSquare.width;
  int y = mouse.y / lightSquare.height;

  int pos_x = x * lightSquare.width;
  int pos_y = y * lightSquare.height;

  if (gameData.selected_pos[0] != -1 && gameData.selected_pos[0] == pos_x &&
      gameData.selected_pos[1] == pos_y) {
    gameData.selected_pos[0] = -1;
    gameData.selected_pos[1] = -1;
  } else {

    gameData.selected_pos[0] = pos_x;
    gameData.selected_pos[1] = pos_y;

    printf("\n%d, %d\n", pos_x, pos_y);
  }
}

#endif // !EVENTS_H
