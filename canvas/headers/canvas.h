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

#ifndef CANVAS
#define CANVAS

#define pixel_size 3

int display_height;
int display_width;
char WINDOW_NAME[] = "Canvas";

int pixel_no = 0;
int rect_no = 0;
int line_no = 0;

bool done = false;
bool hold = false;
float hover_x = 0.0f;
float hover_y = 0.0f;

char pencil_file[] = "D:/CNotes/canvas/UI/assets/pencil_texture.png";
char line_file[] = "D:/CNotes/canvas/UI/assets/line_texture.png";
char eraser_file[] = "D:/CNotes/canvas/UI/assets/eraser_texture.png";
char rectangle_file[] = "D:/CNotes/canvas/UI/assets/rectangle_texture.png";

void log_tool(ToolSelected *current_tool);
bool check_bound(Button_Pos button, float click_x, float click_y);
int main(int argc, char *argv[]);

#endif // !CANVAS
