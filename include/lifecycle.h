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

Uint64 bitboard = 0ULL;

void add_in_position(int bit_pos) { bitboard |= (1ULL << bit_pos); }

Uint64 get_mask(int bit_pos, Uint64 offset) { return ~(offset << bit_pos); };

void remove_piece(int bit_pos) { bitboard &= get_mask(bit_pos, 1ULL); };

typedef enum {
  east = 1,
  west = -1,
  north = -8,
  south = 8,
  nortEast = -7,
  nortWest = -9,
  southWest = 7,
  southEast = 9
} Coord;

void piece_shift(int bit_pos, Coord coord) {
  // Clear the bit
  remove_piece(bit_pos);

  if (gameData.isReversed)
    coord *= -1;

  // Add the bit in the new position
  add_in_position(bit_pos + coord);
}

void print_board() {
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

      printf(" %d", (bitboard & (1ULL << square)) ? 1 : 0);
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

GameData gameData = {PLAYER, {-1, -1}, SDL_FALSE};

void newGame();

void init(void) {

  add_in_position(e3);
  piece_shift(e3, north);

  print_board();

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
