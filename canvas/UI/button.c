#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "button_ui.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

void button_ui(SDL_Window *window, SDL_Renderer *renderer,
               SDL_Surface *image_surface, SDL_Texture *texture,
               SDL_FRect srcrect, SDL_FRect b_srcrect, SDL_FRect dstrect) {

  if (image_surface == NULL) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return;
  }
  SDL_SetRenderDrawColor(renderer, 91, 15, 255, 255);
  SDL_RenderFillRect(renderer, &b_srcrect);
  SDL_RenderTexture(renderer, texture, &srcrect, &dstrect);
  SDL_Event event;
  /*   while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        SDL_PushEvent(&event);
      }
    } */
}
