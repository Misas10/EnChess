#ifndef EVENTS_H
#define EVENTS_H

#include "definitons.h"
#include <stdio.h>

void moveTo(int actual_pos, int next_pos) {
  int rank, nextRank, file, nextFile;
  rank = get_rank(actual_pos);
  file = get_file(actual_pos);

  nextRank = get_rank(next_pos);
  nextFile = get_file(next_pos);

  char piece = boardInfo[rank][file];
  boardInfo[rank][file] = '.';

  boardInfo[nextRank][nextFile] = piece;
}

void showLegalMoves(int square, char piece) {
  Uint64 bitboard;

  switch (piece) {
  case 'n':
  case 'N':
    printf("Knight selected in: %d\n", square);
    bitboard = knight_attacks[1];
    break;
  }

  print_bitboard(bitboard);
}

void mouseClick(SDL_MouseButtonEvent mouse) {

  int x = mouse.x / lightSquare.width;
  int y = mouse.y / lightSquare.height;

  int pos_x = x * lightSquare.width;
  int pos_y = y * lightSquare.height;

  int square = y * 8 + x;

  char piece = boardInfo[y][x];

  // If the square is already selected
  if (gameData.selected_pos[0] != -1 && gameData.selected_pos[0] == pos_x &&
      gameData.selected_pos[1] == pos_y) {

    gameData.selected_pos[0] = -1;
    gameData.selected_pos[1] = -1;

    // If the square is not selected, select it
  } else {
    showLegalMoves(square, piece);

    gameData.selected_pos[0] = pos_x;
    gameData.selected_pos[1] = pos_y;

    if (piece != '.') {
      printf("\n%c\n", boardInfo[y][x]);

      printf("\nSquare selected: %d\n", square);
      moveTo(square, e4);
    }

    printf("\n%d, %d\n", pos_x, pos_y);
    printf("\n%d, %d\n", x, y);
  }
}

#endif // !EVENTS_H
