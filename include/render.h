#ifndef RENDER_H

#define RENDER_H
#include "definitons.h"
#include "events.h"
#include <stdio.h>

Image square;

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

int _getPos(int orientation) {
  return gameData.isReversed ? (7 - orientation) * square.width
                             : orientation * square.width;
}

void _renderAllPieces(int line, int col) {

  char piece = get_piece(col, line);

  if (piece != '.') {
    int bit_pos = get_squareFromCoord(line, col); // line * 8 + col;
    gameData.bitboard = add_in_position(gameData.bitboard, bit_pos);

    int centered_x = (square.width - lightPawn.width) / 2;
    int centered_y = (square.height - lightPawn.height) / 2;

    int pos_x = centered_x + _getPos(col);
    int pos_y = centered_y + _getPos(line);

    renderPiece(piece, pos_x, pos_y);
  }
}

void aux(int line, int col) {
  bool isLight = (line + col) % 2 == 0;
  square = lightSquare;

  if (!isLight)
    square = darkSquare;

  int pos_x = _getPos(col);
  int pos_y = _getPos(line);

  /*printf("Rendering square at col: %d, line: %d, pos_x: %d, pos_y: %d\n", col,
   * line, pos_x, pos_y);*/

  // Render the chessboard squares
  renderImage(square, pos_x, pos_y);
}

void renderLegalMoves(int x, int y) {
  int selected_x = get_file(gameData.selected_pos);
  int selected_y = get_rank(gameData.selected_pos);

  int selected_square = get_squareFromCoord(selected_x, selected_y);
  int current_square = get_squareFromCoord(x, y);

  Uint64 pos_bit = add_in_position(0ULL, current_square);

  Uint64 pieceMove =
      get_legal_bitboard(selected_square, get_piece(selected_x, selected_y));

  // print_bitboard(pieceMove);
  // print_bitboard(pieceMove & pos_bit);

  if ((pos_bit & pieceMove) != 0)
    renderImage(legalMoves, _getPos(x), _getPos(y));
}

void renderChessBoard(int width, int height) {

  SDL_RenderClear(Game.screen.renderer);

  for (int line = 7; line >= 0; line--)
    for (int col = 0; col < 8; col++)
      aux(line, col);

  // Render selected move
  if (gameData.selected_pos != -1) {
    int start_x = _getPos(get_file(gameData.selected_pos));
    int start_y = _getPos(get_rank(gameData.selected_pos));

    renderImage(selected, start_x, start_y);

    /*printf("\n%d %d\n",  start_x, start_y);*/

    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
        renderLegalMoves(i, j);
  }

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      _renderAllPieces(i, j);
}

#endif
