#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "types.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#ifndef BUTTON_UI
#define BUTTON_UI

void render_color_picker(SDL_Renderer *renderer, Color_Picker_Rects rects);

void button_ui(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture,
               SDL_FRect srcrect, SDL_FRect b_srcrect, SDL_FRect dstrect,
               float *mouse_x, float *mouse_y, ToolSelected *selected_tool,
               ToolType which_tool);
#endif // !BUTTON_UI
