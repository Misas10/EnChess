#ifndef LOAD_H
#define LOAD_H

#include "definitons.h"

void loadTextures() {

  int squareSize = Game.screen.w / 8;
  int pieceSize = squareSize * .8;

  lightSquare = svg2Tex(__ASSETS__ "light.svg", squareSize, squareSize);
  lightPawn = svg2Tex(__ASSETS__ "pieces/p.svg", pieceSize, pieceSize);
  lightQueen = svg2Tex(__ASSETS__ "pieces/q.svg", pieceSize, pieceSize);
  lightKing = svg2Tex(__ASSETS__ "pieces/k.svg", pieceSize, pieceSize);
  lightKnight = svg2Tex(__ASSETS__ "pieces/n.svg", pieceSize, pieceSize);
  lightBishop = svg2Tex(__ASSETS__ "pieces/b.svg", pieceSize, pieceSize);
  lightRook = svg2Tex(__ASSETS__ "pieces/r.svg", pieceSize, pieceSize);

  darkSquare = svg2Tex(__ASSETS__ "dark.svg", squareSize, squareSize);
  darkPawn = svg2Tex(__ASSETS__ "pieces/pd.svg", pieceSize, pieceSize);
  darkQueen = svg2Tex(__ASSETS__ "pieces/qd.svg", pieceSize, pieceSize);
  darkKing = svg2Tex(__ASSETS__ "pieces/kd.svg", pieceSize, pieceSize);
  darkKnight = svg2Tex(__ASSETS__ "pieces/nd.svg", pieceSize, pieceSize);
  darkBishop = svg2Tex(__ASSETS__ "pieces/bd.svg", pieceSize, pieceSize);
  darkRook = svg2Tex(__ASSETS__ "pieces/rd.svg", pieceSize, pieceSize);

  selected = svg2Tex(__ASSETS__ "selected.svg", squareSize, squareSize);
}

Image svg2Tex(char *fileName, int width, int height) {

  // Create RAW svg data
  SDL_RWops *rw = SDL_RWFromFile(fileName, "r");
  if (rw == NULL)
    printf("\nError Trying opening the SVG: %s\n", SDL_GetError());

  // Scale SVG with the defined width and height
  SDL_Surface *surface = IMG_LoadSizedSVG_RW(rw, width, height);
  if (surface == NULL)
    printf("\nError Trying to convert image to surface: %s\n", SDL_GetError());

  SDL_Texture *tex =
      SDL_CreateTextureFromSurface(Game.screen.renderer, surface);
  if (tex == NULL)
    printf("\nError Trying to convert SVG to texture: %s\n", SDL_GetError());

  Image image = {tex, width, height};

  SDL_FreeSurface(surface);

  return image;
}

#endif // !LOAD_H
