#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "button_ui.h"
#include "types.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <tools_panel.h>

void render_color_picker(SDL_Renderer *renderer, Color_Picker_Rects rects) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &rects.white);

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(renderer, &rects.red);

  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_RenderFillRect(renderer, &rects.green);

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &rects.blue);
}
void button_ui(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture,
               SDL_FRect srcrect, SDL_FRect b_srcrect, SDL_FRect dstrect,
               float *mouse_x, float *mouse_y, ToolSelected *selected_tool,
               ToolType which_tool) {
  static SDL_FRect last_hover = {0};
  if (texture == NULL) {
    SDL_Log("Failed: %s", SDL_GetError());
    return;
  }

  bool hovered =
      (*mouse_x > b_srcrect.x && *mouse_x < b_srcrect.x + b_srcrect.w &&
       *mouse_y > b_srcrect.y && *mouse_y < b_srcrect.y + b_srcrect.h);

  if (hovered || selected_tool->selected_tool == which_tool) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderFillRect(renderer, &b_srcrect);
  }
  SDL_RenderTexture(renderer, texture, &srcrect, &dstrect);

  // draw button texture (image)
}
