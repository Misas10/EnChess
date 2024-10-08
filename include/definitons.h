#ifndef DEFINITONS_H

#define DEFINITONS_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_NAME "En-Chess"

// Pieces Char representation
#define W_PAWN 'p'
#define W_QUEEN 'q'
#define W_KING 'k'
#define W_BISHOP 'b'
#define W_KNIGHT 'n'
#define W_ROOK 'r'

#define B_PAWN 'P'
#define B_QUEEN 'Q'
#define B_KING 'K'
#define B_BISHOP 'B'
#define B_KNIGHT 'N'
#define B_ROOK 'R'
#define EMPTY '.'

typedef char Board[64];

typedef struct {
  SDL_Texture *tex;
  int width;
  int height;
} Image;

typedef enum { white, black } Player;

typedef struct MoveInfo {
  int move[2];
  struct MoveInfo *next;
  struct MoveInfo *prev;
} MoveInfo;

typedef struct {
  Player player;
  int selected_pos; // from 0 to 63
  MoveInfo moveInfo;
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

typedef enum {
  east = 1,       // right
  west = -1,      // left
  south = 8,      // down
  north = -8,     // up
  northEast = -7, // up Right
  northWest = -9, // up Left
  southWest = 7,  // down Left
  southEast = 9   // down Right
} Direction;

typedef enum {
  noNorthWest = -17,
  noNorthEast = -15,
  weWestNorth = -10,
  eaEastNorth = -6,
  weWestSouth = 6,
  eaEastSouth = 10,
  soSouthWest = 15,
  soSouthEast = 17
} KnightDirection;

// Variables declarations
static const Uint64 notAFile = 0xFEFEFEFEFEFEFEFE;
static const Uint64 notGFile = 0xBFBFBFBFBFBFBFBF;
static const Uint64 notBFile = 0xFDFDFDFDFDFDFDFD;
static const Uint64 notHFile = 0x7F7F7F7F7F7F7F7F;

extern GameData gameData;
extern GameInstance Game;
extern Board boardInfo;

Image lightSquare, lightPawn, lightQueen, lightKing, lightKnight, lightRook,
    lightBishop, darkSquare, darkPawn, darkQueen, darkKing, darkKnight,
    darkRook, darkBishop, selected, legalMoves;

Uint64 pawn_attacks[2][64], king_attacks[64], bishop_attacks[64],
    rook_attacks[64], queen_attacks[64], knight_attacks[64];

//
// Funtions declarations
//
void init(void);
void quit(void);
void render(void);
void print_bitboard(Uint64 bitboard);

Uint64 add_in_position(Uint64 bitboard, int bit_pos);

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

void init_masks();
void init_pawn_mask(int square);
void init_pawn_mask(int square);
void init_bishop_mask(int square);
void init_rook_mask(int square);
void init_queen_attacks(int square);

int get_rank(int square);
int get_file(int square);
int get_squareFromCoord(int x, int y) { return y * 8 + x; }
char get_piece(int x, int y) { return boardInfo[get_squareFromCoord(x, y)]; }

bool is_white(char piece) {
  switch (piece) {
    case W_PAWN:
    case W_KING:
    case W_QUEEN: 
    case W_BISHOP:
    case W_KNIGHT:
    case W_ROOK:
      return true;

    default: return false;
  }

}

bool is_black(char piece) { 
  if(piece == EMPTY) 
    return false;

  return !is_white(piece); 
}

#endif
