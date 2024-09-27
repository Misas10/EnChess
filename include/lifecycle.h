#ifndef LIFECYCLE_H
#define LIFECYCLE_H

#include "definitons.h"

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


Uint64 piece_shift(Uint64 b, Player player, int bit_pos, Direction dir) {
  // Clear the bit
  Uint64 bitboard = remove_piece(bit_pos);
  bitboard = add_in_position(b, bit_pos);

  if (bitboard != b) {
    printf("\n ERROR: Cannot shift, no piece in position: %d \n\n", bit_pos);
    return b;
  }

  if (player == black)
    dir *= -1;

  if (dir == north)
    return bitboard >>= 8;

  else if (dir == south)
    return bitboard <<= 8;

  // To prevent undesireble piece moviment
  if (dir < 0)
    bitboard >>= -dir;

  else
    bitboard <<= dir;

  if (dir == east || dir == northEast || dir == southEast)
    return bitboard & notAFile;

  return bitboard & notHFile;
}

Uint64 pawn_attacks_mask(Player player, int bit_pos) {
  Uint64 bitboard = add_in_position(0ULL, bit_pos);

  return piece_shift(bitboard, player, bit_pos, northEast) |
         piece_shift(bitboard, player, bit_pos, northWest);
}

Uint64 king_attacks_mask(int bit_pos) {
  Uint64 bitboard = add_in_position(0ULL, bit_pos);
  Player player = white;

  return piece_shift(bitboard, player, bit_pos, north) |
         piece_shift(bitboard, player, bit_pos, south) | 
         piece_shift(bitboard, player, bit_pos, northEast) | 
         piece_shift(bitboard, player, bit_pos, northWest) | 
         piece_shift(bitboard, player, bit_pos, southEast) |
         piece_shift(bitboard, player, bit_pos, southWest) | 
         piece_shift(bitboard, player, bit_pos, east) |
         piece_shift(bitboard, player, bit_pos, west);

}

void init_pawn_mask(int square) {
  pawn_attacks[white][square] = pawn_attacks_mask(white, square);
  pawn_attacks[black][square] = pawn_attacks_mask(black, square);
}

void init_king_mask(int square) {
  king_attacks[square] = king_attacks_mask(square);
}

void init_masks() {
  for (int square = 0; square < 64; square++) {
    init_pawn_mask(square);
    init_king_mask(square);
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
  gameData.bitboard = add_in_position(0ULL, g1);
  /*print_bitboard(piece_shift(gameData.bitboard, white, g1, east));*/
  /*print_bitboard((pawn_attacks[white][h3]));*/
  /*print_bitboard((king_attacks[h3]));*/

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
