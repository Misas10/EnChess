#ifndef DEFINITONS_H

#define DEFINITONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_NAME "En-Chess" 

typedef char Board[8][8];

typedef struct {
  SDL_Texture *tex;
  int width;
  int height;
} Image;

typedef struct {
  Board board;
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
   GameData data;
} GameInstance;

GameInstance Game;

void init(void);
void quit(void);
void render(void);

void renderSVG(Image image, int x, int y);
/*
 * Render an SVG image in a x, y position
 */

void svg2Tex();

#endif
