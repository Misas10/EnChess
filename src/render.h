#ifndef RENDER_H

#define RENDER_H
#include "definitons.h"

void render() {
  renderChessBoard(Game.screen.w, Game.screen.h);

  SDL_RenderPresent(Game.screen.renderer);
}

// TODO: Optimize, and only load all the necessary files once
void renderChessBoard(int width, int height) {
  /*light */
  int squareSize = WINDOW_WIDTH / 8;

  lightSquare = svg2Tex(__ASSETS__ "light.svg", squareSize, squareSize);
  darkSquare = svg2Tex(__ASSETS__ "dark.svg", squareSize, squareSize);

  lightPawn = svg2Tex(__ASSETS__ "pieces/p.svg", squareSize / 2, squareSize / 2);
  darkPawn = svg2Tex(__ASSETS__ "pieces/pd.svg", squareSize / 2, squareSize / 2);

  SDL_Rect squareRect;
  squareRect.w = lightSquare.width;
  squareRect.h = lightSquare.height;

  SDL_Rect pieceRect; 
  pieceRect.w = lightPawn.width;
  pieceRect.h = lightPawn.height;

  for(int line = 0; line < 8; line++){

    for (int col = 0; col < 8; col++) {
      bool isLight = (line + col) % 2 == 0;
      Image square, piece;

      if(isLight)
        square = lightSquare;

      else
        square = darkSquare;

      squareRect.x = line * square.width;
      squareRect.y = col * square.height;

      SDL_RenderCopy(Game.screen.renderer, square.tex, NULL, &squareRect);
      /*SDL_RenderCopy(Game.screen.renderer, piece.tex, NULL, &pieceRect);*/
    }
  }

}

#endif

