#include "common.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
// #include <stdio.h>

bool is_game_running = true;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

bool init() {
  int init_video = SDL_Init(SDL_INIT_VIDEO);
  int init_events = SDL_Init(SDL_INIT_EVENTS);

  if (init_video < 0 || init_events < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s",
                 SDL_GetError());
    return false;
  }

  if (SDL_CreateWindowAndRenderer("EnChess", WINDOW_WIDTH, WINDOW_HEIGHT,
                                  SDL_WINDOW_METAL, &window, &renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Couldn't create window and renderer: %s", SDL_GetError());
    return false;
  }

  return true;
}

void events() {
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_EVENT_QUIT:
    is_game_running = false;
    break;
  }
}

void render() {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(renderer);
}

void quit() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
}

int main() {
  init();

  while (is_game_running) {
    events();
    render();
  }

  quit();
  return 0;
}
