#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "headers/line_tool.h"
#include "headers/pencil_tools.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define pixel_size 3

int display_height;
int display_width;
char WINDOW_NAME[] = "Canvas";
int rect_no = 0;
int line_no = 0;
bool done = false;
bool hold = false;

int main(int argc, char *argv[]) {
  SDL_FRect *pixel_storage = NULL;
  Line *line_storage = NULL;

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return -1;
  }

  SDL_Window *window = SDL_CreateWindow(
      WINDOW_NAME, 1920, 1080, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
  if (!window) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  SDL_GetWindowSizeInPixels(window, &display_width, &display_height);

  SDL_Log("Display size: %d x %d", display_width, display_height);
  while (!done) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        done = true;
        break;
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        hold = true;
        line_tool(&line_storage, &line_no, event.button.x, event.button.y);
        break;
      case SDL_EVENT_MOUSE_BUTTON_UP:
        hold = false;
        break;
      case SDL_EVENT_MOUSE_MOTION:
        pencil_tool(renderer, &hold, &rect_no, &pixel_storage, event.motion.x,
                    event.motion.y, (float)(display_width * display_height));
        if (hold && line_no > 0) {
          (line_storage)[line_no - 1].x2 = event.motion.x;
          (line_storage)[line_no - 1].y2 = event.motion.y;
        }
        break;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    /* if (rect_no > 0) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderFillRects(renderer, pixel_storage, rect_no);
    } */
    if (line_no > 0) {
      for (int i = 0; i < line_no; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderLine(renderer, (line_storage)[i].x1, (line_storage)[i].y1,
                       (line_storage)[i].x2, (line_storage)[i].y2);
      }
    }
    SDL_RenderPresent(renderer);
  }

  free(pixel_storage);
  free(line_storage);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
