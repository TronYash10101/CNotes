#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "pen_tool.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

#ifndef ERASER_TOOL
#define ERASER_TOOL

extern int eraser_size;

void point_eraser(Pixel **pixel_storage_ptr, float mouse_x, float mouse_y,
                  int rect_no);

#endif // !LINE_TOOL
