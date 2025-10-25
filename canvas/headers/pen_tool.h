#ifndef PENCIL_TOOL
#define PENCIL_TOOL

#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define pixel_size 3
extern Uint32 PEN_TOOL_EVENT;
typedef struct {
  SDL_FRect pixel;
  bool visible;
} Pixel;

void pencil_tool(SDL_Renderer *renderer, bool *hold_ptr, int *pixel_no_ptr,
                 Pixel **pixel_storage_ptr, float x_coord, float y_coord,
                 float display_size);

#endif // !PENCIL_TOOL
