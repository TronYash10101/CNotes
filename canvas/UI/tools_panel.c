#include "tools_panel.h"
#include "SDL3/SDL_render.h"

Button_Pos pen_button = {
    {0.0f, 0.0f, 500.0f, 500.0f},
    {SCALE_X(1800.0f), 200.0f, icon_height, icon_width},
    {SCALE_X(1795.0f), 195.0f, button_height, button_width}};

Button_Pos line_button = {
    {0.0f, 0.0f, 500.0f, 500.0f},
    {SCALE_X(1800.0f), (200.0f + button_gap), icon_height, icon_width},
    {SCALE_X(1795.0f), (195.0f + button_gap), button_height, button_width}};

Button_Pos eraser_button = {
    {0.0f, 0.0f, 500.0f, 500.0f},
    {SCALE_X(1800.0f), 200.0f + (2 * button_gap), icon_height, icon_width},
    {SCALE_X(1795.0f), 195.0f + (2 * button_gap), button_height, button_width}};

Button_Pos rectangle_button = {
    {0.0f, 0.0f, 500.0f, 500.0f},
    {SCALE_X(1800.0f), 200.0f + (3 * button_gap), icon_height, icon_width},
    {SCALE_X(1795.0f), 195.0f + (3 * button_gap), button_height, button_width}};

Color_Picker_Rects color_picker_rects = {
    {SCALE_X(1795.0f), 195.0f + (4 * button_gap), button_height - 20,
     button_width - 20},
    {SCALE_X(1850.0f), 195.0f + (4 * button_gap), button_height - 20,
     button_width - 20},
    {SCALE_X(1795.0f), 195.0f + (4.5 * button_gap), button_height - 20,
     button_width - 20},
    {SCALE_X(1850.0f), 195.0f + (4.5 * button_gap), button_height - 20,
     button_width - 20}};

/* Uint32 PEN_TOOL_EVENT;
Uint32 LINE_TOOL_EVENT; */

void tool_panel(SDL_Window *window, SDL_Renderer *renderer,
                SDL_Texture *pencil_texture, SDL_Texture *line_texture,
                SDL_Texture *eraser_texture, SDL_Texture *rectangle_texture,
                bool *done, float *mouse_x, float *mouse_y,
                ToolSelected *selected_tool) {
  int width = 1420;
  int height = 1080;
  SDL_GetWindowSizeInPixels(window, &width, &height);
  *mouse_x = SCALE_X(*mouse_x);

  SDL_FRect tools_panel_bg = {SCALE_X(1780.0f), 185.0f, 130.0f, 390.0f};
  SDL_FRect shadow = {SCALE_X(1770.0f), 195.0f, 130.0f, 390.0f};
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 35, 35, 41, 255);
  SDL_RenderFillRect(renderer, &tools_panel_bg);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 60);
  SDL_RenderFillRect(renderer, &shadow);
  // Draw texture
  button_ui(window, renderer, pencil_texture, pen_button.srcrect,
            pen_button.bg_rcrect, pen_button.drcrect, mouse_x, mouse_y,
            selected_tool, TOOL_PEN);
  button_ui(window, renderer, line_texture, line_button.srcrect,
            line_button.bg_rcrect, line_button.drcrect, mouse_x, mouse_y,
            selected_tool, TOOL_LINE);
  button_ui(window, renderer, eraser_texture, eraser_button.srcrect,
            eraser_button.bg_rcrect, eraser_button.drcrect, mouse_x, mouse_y,
            selected_tool, TOOL_ERASER);
  button_ui(window, renderer, rectangle_texture, rectangle_button.srcrect,
            rectangle_button.bg_rcrect, rectangle_button.drcrect, mouse_x,
            mouse_y, selected_tool, TOOL_RECTANGLE);
  render_color_picker(renderer, color_picker_rects);
}
