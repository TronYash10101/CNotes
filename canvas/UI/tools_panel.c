#include "tools_panel.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "button_ui.h"
#include "line_tool.h"
#include "pen_tool.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

Button_Pos pen_button = {{0.0f, 0.0f, 500.0f, 500.0f},
                         {200.0f, 200.0f, 50.0f, 50.0f},
                         {200.0f, 200.0f, 50.0f, 50.0f}};

Button_Pos line_button = {{0.0f, 0.0f, 500.0f, 500.0f},
                          {600.0f, 200.0f, 50.0f, 50.0f},
                          {600.0f, 200.0f, 50.0f, 50.0f}};
Uint32 PEN_TOOL_EVENT;
Uint32 LINE_TOOL_EVENT;
void tool_panel(SDL_Window *window, SDL_Renderer *renderer,
                SDL_Surface *pencil_surface, SDL_Surface *line_surface,
                SDL_Texture *pencil_texture, SDL_Texture *line_texture,
                bool *done) {

  int width = 1920;
  int height = 1080;
  SDL_GetWindowSizeInPixels(window, &width, &height);

  PEN_TOOL_EVENT = SDL_RegisterEvents(1);
  LINE_TOOL_EVENT = SDL_RegisterEvents(1);

  button_ui(window, renderer, pencil_surface, pencil_texture,
            pen_button.srcrect, pen_button.bg_rcrect, pen_button.drcrect);
  button_ui(window, renderer, line_surface, line_texture, line_button.srcrect,
            line_button.bg_rcrect, line_button.drcrect);
}
