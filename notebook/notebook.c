#include "SDL3/SDL.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_textengine.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <stdbool.h>
#include <stdio.h>

char title[] = "Notebook";
char greet[] = "Hello";
int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  bool done = false;

  SDL_Window *window = SDL_CreateWindow(
      title, 1920, 1080, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  if (window == NULL || renderer == NULL) {
    SDL_Log("Could not create window or renderer");
    return -1;
  }
  TTF_TextEngine *engine = TTF_CreateRendererTextEngine(renderer);
  if (engine == NULL) {
    SDL_Log("Text engine error");
  }
  TTF_Font *font = TTF_OpenFont("D:/CNotes/notebook/fonts/arial.ttf", 48);
  if (font == NULL) {
    SDL_Log("Text engine error");
  }

  // Create a text object
  TTF_Text *myText = TTF_CreateText(engine, font, "Hello World!", 0);
  if (!myText) {
    SDL_Log("Text engine error");
  }
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        done = true;
      }
    }
    SDL_RenderClear(renderer);
    TTF_DrawRendererText(myText, 100.0f, 100.0f);
    SDL_RenderPresent(renderer);
  }
  TTF_DestroyText(myText);
  TTF_CloseFont(font);
  TTF_DestroyRendererTextEngine(engine);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
