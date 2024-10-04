#ifndef EVENTS_H
#define EVENTS_H

#include "definitons.h"

void moveTo(int actual_pos, int next_pos) {
  int rank, nextRank, file, nextFile;
  rank = get_rank(actual_pos);
  file = get_file(actual_pos);

  nextRank = get_rank(next_pos);
  nextFile = get_file(next_pos);

  char piece = boardInfo[rank][file];
  boardInfo[rank][file] = EMPTY;

  boardInfo[nextRank][nextFile] = piece;
}

// TODO: ADICIONAR A PARTE DOS PEÕES

Uint64 get_legal_bitboard(int square, char piece) {
  Uint64 bitboard = 0ULL;

  switch (piece) {
  case W_KNIGHT:
  case B_KNIGHT:
    bitboard = knight_attacks[square];
    break;

  case W_BISHOP:
  case B_BISHOP:
    bitboard = bishop_attacks[square];
    break;

  case W_ROOK:
  case B_ROOK:
    bitboard = rook_attacks[square];
    break;

  case W_QUEEN:
  case B_QUEEN:
    bitboard = queen_attacks[square];
    break;

  case W_KING:
  case B_KING:
    bitboard = king_attacks[square];
    break;
  }

  return bitboard; // ^ gameData.bitboard;
}

void mouseClick(SDL_MouseButtonEvent mouse) {

  int x = mouse.x / lightSquare.width;
  int y = mouse.y / lightSquare.height;

  int pos_x = x * lightSquare.width;
  int pos_y = y * lightSquare.height;

  int square = get_squareFromCoord(x, y);

  char piece = boardInfo[y][x];

  // If the square is already selected
  if (gameData.selected_pos != -1) {
    // Check if is the square it self
    if (square == gameData.selected_pos)
      gameData.selected_pos = -1;

    // Check if is any other square
    else {
      gameData.selected_pos = square;
      gameData.moveInfo.move[0] = gameData.selected_pos;
      gameData.moveInfo.move[1] = square;
    }

    // If the square is not selected, select it
  } else {
    // print_bitboard(get_legal_bitboard(square, piece));

    gameData.selected_pos = square;

    if (piece != '.') {
      printf("\n%c\n", get_piece(x, y));

      printf("\nSquare selected: %d\n", square);
      /*moveTo(square, e4);*/
    }

    printf("\n%d, %d\n", pos_x, pos_y);
    printf("\n%d, %d\n", x, y);
  }
}

#endif // !EVENTS_H
