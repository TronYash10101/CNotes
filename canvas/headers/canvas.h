#ifndef CANVAS
#define CANVAS

#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "eraser_tool.h"
#include "line_tool.h"
#include "pen_tool.h"
#include "rectangle_tool.h"
#include "tools_panel.h"
#include "types.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define pixel_size 3

extern int display_height;
extern int display_width;
extern char WINDOW_NAME[];

extern int pixel_no;
extern int rect_no;
extern int line_no;

extern float hover_x;
extern float hover_y;

extern char pencil_file[];
extern char line_file[];
extern char eraser_file[];
extern char rectangle_file[];

void log_tool(ToolSelected *current_tool);
bool check_bound(Button_Pos button, float click_x, float click_y);
int canvas(SDL_Window *window, SDL_Renderer *renderer, bool *done,
           SDL_Event *event_ptr, Pixel **pixel_storage, Line **line_storage,
           Rectangle **rectangle_storage, SDL_Texture *pencil_texture,
           SDL_Texture *line_texture, SDL_Texture *eraser_texture,
           SDL_Texture *rectangle_texture);

#endif // !CANVAS
