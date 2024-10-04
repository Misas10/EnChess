#ifndef LIFECYCLE_H
#define LIFECYCLE_H

#include "bitboard.h"
// #include "definitons.h"

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

// char board_info[64] = {
//     'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', 'P', 'P', 'P', 'P', 'P',
//     'P', 'P', 'P', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
//     '.', '.', '.', '.', '.', '.', '.', '.', '.', 'p', 'p', 'p', 'p',
//     'p', 'p', 'p', 'p', 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
// };

GameInstance Game = {
    SDL_FALSE,
    {WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL},
    init,
    quit,
};

GameData gameData = {white, -1, SDL_FALSE};

void newGame();

void init(void) {
  clock_t t;

  t = clock();
  init_masks();
  t = clock() - t;
  double time_taken = ((double)t) / CLOCKS_PER_SEC;

  // int square = 0;
  // gameData.bitboard = add_in_position(0ULL, 4);
  /*print_bitboard(piece_shift(gameData.bitboard, white, g1, east));*/
  /*print_bitboard((pawn_attacks[white][h3]));*/
  /*print_bitboard(king_attacks[a5]);*/
  // print_bitboard(pawn_move(a6, black));

  printf("\nBitboard value: %llu \n", gameData.bitboard);
  printf("Genereted all bitboard masks in: %fs \n\n", time_taken);

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

  SDL_SetWindowFullscreen(Game.screen.window, 0);

  printf("Rendering window\n");
  // Rendering the window
  Game.screen.renderer =
      SDL_CreateRenderer(Game.screen.window, -1, SDL_RENDERER_ACCELERATED);

  if (Game.screen.renderer == NULL) {
    printf("Failed to create renderer: %s", SDL_GetError());
    Game.isRunning = SDL_FALSE;
    return;
  }

  Game.isRunning = SDL_TRUE;
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
