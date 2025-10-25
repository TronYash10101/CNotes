#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef RECTANGLE_TOOL
#define RECTANGLE_TOOL
// Repeated like Pixel type
typedef struct {
  SDL_FRect Rectangle;
  bool visible;
} Rectangle;

void rectangle_tool(Rectangle **rectangle_storage_ptr, float rect_x,
                    float rect_y, int *rect_no_ptr);
#endif // !RECTANGLE_TOOL
