#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
int display_width;
int display_height;
char title[] = "pen tool";

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

char pencil_file[] = "D:/CNotes/canvas/UI/pencil_texture.png";

int main(int argc, char *argv[]) {
  bool done = false;
  SDL_Surface *IMG_Load(const char *file);
  SDL_Surface *surface = IMG_Load(pencil_file);

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return -1;
  }
  if (surface == NULL) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return -1;
  }
  if (!SDL_CreateWindowAndRenderer(title, display_width, display_height,
                                   SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED,
                                   &window, &renderer)) {
    printf("Could not create window or renderer");
    return -1;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
  SDL_GetWindowSizeInPixels(window, &display_width, &display_height);
  SDL_FRect srcrect = {0.0f, 0.0f, 500.0f, 500.0f};     // Crop from texture
  SDL_FRect b_srcrect = {200.0f, 200.0f, 64.0f, 64.0f}; // background
  SDL_FRect dstrect = {200.0f, 200.0f, 64.0f, 64.0f};
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        done = true;
        break;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 15, 255, 255);
    SDL_RenderFillRect(renderer, &b_srcrect);
    SDL_RenderTexture(renderer, texture, &srcrect, &dstrect);

    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_DestroyTexture(texture);
  SDL_Quit();
  return 0;
}
