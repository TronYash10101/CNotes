#include "tools_panel.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"
#include "button_ui.h"
#include "eraser_tool.h"
#include "line_tool.h"
#include "pen_tool.h"
#include "rectangle_tool.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

SDL_FRect tools_panel_bg = {1680.0f, 150.0f, 50.0f, 40.0f};

Button_Pos pen_button = {{0.0f, 0.0f, 500.0f, 500.0f},
                         {1800.0f, 200.0f, icon_height, icon_width},
                         {1795.0f, 195.0f, button_height, button_width}};

Button_Pos line_button = {
    {0.0f, 0.0f, 500.0f, 500.0f},
    {1800.0f, (200.0f + button_gap), icon_height, icon_width},
    {1795.0f, (195.0f + button_gap), button_height, button_width}};
Button_Pos eraser_button = {
    {0.0f, 0.0f, 500.0f, 500.0f},
    {1800.0f, 200.0f + (2 * button_gap), icon_height, icon_width},
    {1795.0f, 195.0f + (2 * button_gap), button_height, button_width}};
Button_Pos rectangle_button = {
    {0.0f, 0.0f, 500.0f, 500.0f},
    {1800.0f, 200.0f + (3 * button_gap), icon_height, icon_width},
    {1795.0f, 195.0f + (3 * button_gap), button_height, button_width}};

Uint32 PEN_TOOL_EVENT;
Uint32 LINE_TOOL_EVENT;
void tool_panel(SDL_Window *window, SDL_Renderer *renderer,
                SDL_Texture *pencil_texture, SDL_Texture *line_texture,
                SDL_Texture *eraser_texture, SDL_Texture *rectangle_texture,
                SDL_Texture *tool_panel_texture, bool *done, bool *hovered) {
  int width = 1920;
  int height = 1080;
  SDL_GetWindowSizeInPixels(window, &width, &height);

  PEN_TOOL_EVENT = SDL_RegisterEvents(1);
  LINE_TOOL_EVENT = SDL_RegisterEvents(1);

  // Draw texture
  SDL_RenderTexture(renderer, tool_panel_texture, NULL, &tools_panel_bg);
  button_ui(window, renderer, pencil_texture, pen_button.srcrect,
            pen_button.bg_rcrect, pen_button.drcrect, hovered);
  button_ui(window, renderer, line_texture, line_button.srcrect,
            line_button.bg_rcrect, line_button.drcrect, hovered);
  button_ui(window, renderer, eraser_texture, eraser_button.srcrect,
            eraser_button.bg_rcrect, eraser_button.drcrect, hovered);
  button_ui(window, renderer, rectangle_texture, rectangle_button.srcrect,
            rectangle_button.bg_rcrect, rectangle_button.drcrect, hovered);
}
