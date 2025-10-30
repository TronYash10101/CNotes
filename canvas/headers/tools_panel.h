#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "button_ui.h"
#include "eraser_tool.h"
#include "line_tool.h"
#include "rectangle_tool.h"
#include "types.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#define icon_height 35
#define icon_width 35
#define button_height 45
#define button_width 45
#define button_gap 70.0f

#ifndef TOOLS_PANEL
#define TOOLS_PANEL

typedef struct {
  SDL_FRect srcrect;
  SDL_FRect drcrect;
  SDL_FRect bg_rcrect;

} Button_Pos;

extern char title[];
extern char pencil_file[];
extern char line_file[];

extern Button_Pos pen_button;
extern Button_Pos line_button;
extern Button_Pos eraser_button;
extern Button_Pos rectangle_button;
extern void tool_panel(SDL_Window *window, SDL_Renderer *renderer,
                       SDL_Texture *pencil_texture, SDL_Texture *line_texture,
                       SDL_Texture *eraser_texture,
                       SDL_Texture *rectangle_texture, bool *done,
                       float *mouse_x, float *mouse_y,
                       ToolSelected *selected_tool);

#endif // !TOOLS_PANEL
