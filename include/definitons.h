#ifndef DEFINITONS_H

#define DEFINITONS_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_NAME "En-Chess"

typedef char Board[8][8];

typedef struct {
  SDL_Texture *tex;
  int width;
  int height;
} Image;

typedef enum { white, black } Player;

typedef struct {
  Player player;
  int selected_pos[2];
  SDL_bool isReversed;
  Uint64 bitboard;
} GameData;

typedef struct {
  SDL_bool isRunning;
  struct {
    unsigned int w;
    unsigned int h;
    const char *name;
    SDL_Window *window;
    SDL_Renderer *renderer;
  } screen;

  void (*init)(void);
  void (*quit)(void);
} GameInstance;

// Copy from bitboard values after setting 0s in the files/ranks
const Uint64 notAFile = 0xFEFEFEFEFEFEFEFE;
const Uint64 notHFile = 0x7F7F7F7F7F7F7F7F;

enum {
  a8,
  b8,
  c8,
  d8,
  e8,
  f8,
  g8,
  h8,
  a7,
  b7,
  c7,
  d7,
  e7,
  f7,
  g7,
  h7,
  a6,
  b6,
  c6,
  d6,
  e6,
  f6,
  g6,
  h6,
  a5,
  b5,
  c5,
  d5,
  e5,
  f5,
  g5,
  h5,
  a4,
  b4,
  c4,
  d4,
  e4,
  f4,
  g4,
  h4,
  a3,
  b3,
  c3,
  d3,
  e3,
  f3,
  g3,
  h3,
  a2,
  b2,
  c2,
  d2,
  e2,
  f2,
  g2,
  h2,
  a1,
  b1,
  c1,
  d1,
  e1,
  f1,
  g1,
  h1,
};

extern GameData gameData;
extern GameInstance Game;
extern Board boardInfo;

Image lightSquare, lightPawn, lightQueen, lightKing, lightKnight, lightRook,
    lightBishop, darkSquare, darkPawn, darkQueen, darkKing, darkKnight,
    darkRook, darkBishop, selected;

void init(void);
void quit(void);
void render(void);
void print_bitboard(Uint64 bitboard);

/*void renderSVG(Image image, int x, int y);*/
/*
 * Render an SVG image in a x, y position
 */

Image svg2Tex(char *fileName, int width, int height);
/*
 * Convert svg to a texture for rendering
 */

void renderChessBoard(int width, int height);
/*
 *
 */

void renderImage(Image image, int x, int y);

void loadTextures();

#endif
