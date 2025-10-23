#ifndef PENCIL_TOOL
#define PENCIL_TOOL

#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define pixel_size 3
extern Uint32 PEN_TOOL_EVENT;
void pencil_tool(SDL_Renderer *renderer, bool *hold_ptr, int *rect_no_ptr,
                 SDL_FRect **pixel_storage_ptr, float x_coord, float y_coord,
                 float display_size);

#endif // !PENCIL_TOOL
