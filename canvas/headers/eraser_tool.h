#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "line_tool.h"
#include "pen_tool.h"
#include "rectangle_tool.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

#ifndef ERASER_TOOL
#define ERASER_TOOL

void point_eraser(Pixel **pixel_storage_ptr, float mouse_x, float mouse_y,
                  int rect_no);
void line_eraser(Line **line_storage_ptr, float mouse_x, float mouse_y,
                 int line_no);
void rectangle_eraser(Rectangle **rectangle_storage, int rect_no, float mouse_x,
                      float mouse_y);

#endif // !LINE_TOOL
