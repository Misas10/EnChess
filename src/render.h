#ifndef RENDER_H

#define RENDER_H
#include "definitons.h"
#include <stdio.h>

void render() {
  renderChessBoard(Game.screen.w, Game.screen.h);

  SDL_RenderPresent(Game.screen.renderer);
}

void renderImage(Image image, int x, int y) {

  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = image.width;
  rect.h = image.height;

  SDL_RenderCopy(Game.screen.renderer, image.tex, NULL, &rect);
}

void renderPiece(char code, int x, int y) {


  switch (code) {
    case 'p':
      renderImage(lightPawn, x, y);
      break;

    case 'q':
      renderImage(lightQueen, x, y);
      break;

    case 'k':
      renderImage(lightKing, x, y);
      break;

    case 'n':
      renderImage(lightKnight, x, y);
      break;

    case 'b':
      renderImage(lightBishop, x, y);
      break;

    case 'r':
      renderImage(lightRook, x, y);
      break;

    case 'P':
      renderImage(darkPawn, x, y);
      break;

    case 'Q':
      renderImage(darkQueen, x, y);
      break;

    case 'K':
      renderImage(darkKing, x, y);
      break;

    case 'N':
      renderImage(darkKnight, x, y);
      break;

    case 'B':
      renderImage(darkBishop, x, y);
      break;

    case 'R':
      renderImage(darkRook, x, y);
      break;

    default:
      printf("ERROR: piece code %c is invalid!", code);
      break;
  }
}

void aux(int line, int col) {
    bool isLight = (line + col) % 2 == 0;

    /*if(gameData.isReversed)*/
    /*  isLight = !isLight;*/

    Image square = lightSquare;

    if(!isLight)
      square = darkSquare;

    int pos_x = gameData.isReversed ? (7 - col) * square.width : col * square.width;
    int pos_y = gameData.isReversed ? (7 - line) * square.height : line * square.height;

    /*printf("Rendering square at col: %d, line: %d, pos_x: %d, pos_y: %d\n", col, line, pos_x, pos_y);*/

    renderImage(square, pos_x, pos_y);

    char piece = boardInfo[line][col];

    if(piece != '.'){
      int centered_x = (square.width - lightPawn.width) / 2;
      int centered_y = (square.height - lightPawn.height) / 2;

      pos_x = gameData.isReversed ? centered_x + (7 - col) * square.width : centered_x + col * square.width;
      pos_y = gameData.isReversed ? centered_y + (7 - line) * square.height : centered_y + line * square.height;

      /*printf("Rendering piece %c at col: %d, line: %d, pos_x: %d, pos_y: %d\n", piece, col, line, pos_x, pos_y);*/

      renderPiece(piece, pos_x, pos_y);
    }

}

void renderChessBoard(int width, int height) {

  SDL_RenderClear(Game.screen.renderer);

    for(int line = 7; line >= 0; line--)
      for (int col = 0; col < 8; col++) 
        aux(line, col);

}

#endif

