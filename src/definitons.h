#ifndef DEFINITONS_H

#define DEFINITONS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_NAME "En-Chess" 

typedef char Board[8][8];

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

#endif
