#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "button_ui.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <tools_panel.h>

/* bool check_bound(Button_Pos button, float event.button.motion, float click_y)
{ bool in_bound = false; if (event.button.motion >= button.bg_rcrect.x &&
      event.button.motion <= button.bg_rcrect.x + button.bg_rcrect.w &&
      click_y >= button.bg_rcrect.y &&
      click_y <= button.bg_rcrect.y + button.bg_rcrect.h) {
    in_bound = true;
  }
  return in_bound;
} */
void button_ui(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture,
               SDL_FRect srcrect, SDL_FRect b_srcrect, SDL_FRect dstrect,
               bool *hovered) {
  SDL_Event event;
  if (texture == NULL) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return;
  }
  SDL_SetRenderDrawColor(renderer, 91, 15, 255, 120);
  if (*hovered) {
    SDL_RenderFillRect(renderer, &b_srcrect);
  }
  SDL_RenderTexture(renderer, texture, &srcrect, &dstrect);
}
