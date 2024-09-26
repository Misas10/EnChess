#ifndef LIFECYCLE_H
#define LIFECYCLE_H

#include "SDL_stdinc.h"
#include "definitons.h"
#include "render.h"
#include <stdio.h>

Board boardInfo = {
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
};

Uint64 add_in_position(Uint64 bitboard, int bit_pos) {
  return bitboard | (1ULL << bit_pos);
}

Uint64 get_mask(int bit_pos, Uint64 offset) { return ~(offset << bit_pos); };

Uint64 remove_piece(int bit_pos) {
  return gameData.bitboard & get_mask(bit_pos, 1ULL);
};

typedef enum {
  east = 1,
  west = -1,
  south = 8,
  north = -8,
  northEast = -7,
  northWest = -9,
  southWest = 7,
  southEast = 9
} Direction;

Uint64 piece_shift(Uint64 b, int bit_pos, Direction dir) {
  // Clear the bit
  Uint64 bitboard = remove_piece(bit_pos);
  bitboard = add_in_position(b, bit_pos);

  if (bitboard != b) {
    printf("\n ERROR: Cannot shift, no piece in position: %d \n\n", bit_pos);
    return b;
  }

  if (gameData.player == black)
    dir *= -1;

  if (dir == north)
    return bitboard >>= 8;

  else if (dir == south)
    return bitboard <<= 8;

  // To prevent undesireble piece moviment
  if (dir < 0)
    bitboard >>= -dir;

  else
    bitboard <<= dir; //& notHFile;

  if (dir == west || dir == northEast || dir == southEast)
    return bitboard & notAFile;

  return bitboard & notHFile;
}

Uint64 pawn_attacks[2][64];

Uint64 pawn_attacks_mask(Player player, int bit_pos) {
  Uint64 bitboard = add_in_position(0ULL, bit_pos);

  return piece_shift(bitboard, bit_pos, northEast) |
         piece_shift(bitboard, bit_pos, northWest);
  //
  Uint64 attacks = 0ULL;

  if (player == white) {
    if ((bitboard >> -northEast) & notAFile)
      attacks |= (bitboard >> -northEast);

    if ((bitboard << northWest) & notHFile)
      attacks |= (bitboard << northWest);
  }

  else {
    if ((bitboard << northWest) & notAFile)
      attacks |= (bitboard << northWest);
  }

  return attacks;
}

void init_masks() {
  for (int square = 0; square < 64; square++) {
    printf("%d \n", square);
    print_bitboard(pawn_attacks_mask(white, square));
    printf("\n");
    // pawn_attacks[white][square] = pawn_attacks_mask(white, square);
    // pawn_attacks[black][square] = pawn_attacks_mask(black, square);
  }
}

void print_bitboard(Uint64 bitboard) {
  printf("   ");
  for (int i = 'a'; i < 'a' + 8; i++)
    printf(" %c", i);

  printf("\n");

  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      // Calculate square with the coordinates
      int square = rank * 8 + file;

      if (!file)
        printf(" %d ", 8 - rank);

      printf(" %c", (bitboard & (1ULL << square)) ? '1' : '0');
    }
    printf("\n");
  }
}

GameInstance Game = {
    SDL_FALSE,
    {WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL},
    init,
    quit,
};

GameData gameData = {white, {-1, -1}, SDL_FALSE};

void newGame();

void init(void) {

  init_masks();

  int square = 0;
  gameData.bitboard = add_in_position(0ULL, c7);
  // gameData.bitboard = add_in_position(gameData.bitboard, 10);
  // piece_shift(gameData.bitboard, c7, north);
  // piece_shift(gameData.bitboard, c7, south);
  //
  // piece_shift(gameData.bitboard, c7, east);
  // piece_shift(gameData.bitboard, c7, west);
  //
  // piece_shift(gameData.bitboard, c7, southEast);
  // piece_shift(gameData.bitboard, c7, southWest);
  //
  // piece_shift(gameData.bitboard, c7, northEast);
  // piece_shift(gameData.bitboard, c7, northWest);
  // print_bitboard(gameData.bitboard);
  //
  // /*add_in_position(h1);*/
  // print_bitboard(pawn_attacks[white][b1]);
  gameData.bitboard = piece_shift(gameData.bitboard, c7, northEast) |
                      piece_shift(gameData.bitboard, c7, northWest);
  // print_bitboard(gameData.bitboard);
  // gameData.bitboard = add_in_position(0ULL, a1);
  // gameData.bitboard = piece_shift(gameData.bitboard, a1, northWest);

  printf("\nBitboard value: %llu \n\n", gameData.bitboard);

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError(),
                             NULL);
    exit(1);
  }

  printf("Starting\n");

  // Starting the window
  Game.screen.window = SDL_CreateWindow(
      Game.screen.name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      Game.screen.w, Game.screen.h, SDL_WINDOW_RESIZABLE);

  if (Game.screen.window == NULL) {
    printf("Failed to create window: %s", SDL_GetError());
    Game.isRunning = SDL_FALSE;
    return;
  }

  /*SDL_SetWindowFullscreen(Game.screen.window, 0);*/

  printf("Rendering window\n");
  // Rendering the window
  Game.screen.renderer =
      SDL_CreateRenderer(Game.screen.window, -1, SDL_RENDERER_ACCELERATED);

  if (Game.screen.renderer == NULL) {
    printf("Failed to create renderer: %s", SDL_GetError());
    Game.isRunning = SDL_FALSE;
    return;
  }

  // Game.isRunning = SDL_TRUE;

  /*memmove(Game.data.board, boardData, sizeof(Board));*/
};

void quit(void) {
  SDL_DestroyWindow(Game.screen.window);
  SDL_DestroyRenderer(Game.screen.renderer);

  SDL_DestroyTexture(lightSquare.tex);
  SDL_DestroyTexture(darkSquare.tex);

  SDL_DestroyTexture(lightPawn.tex);
  SDL_DestroyTexture(darkPawn.tex);
  SDL_Quit();
};

#endif
