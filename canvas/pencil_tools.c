#include "headers/pencil_tools.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void pencil_tool(SDL_Renderer *renderer, bool *hold_ptr, int *rect_no_ptr,
                 SDL_FRect **pixel_storage_ptr, float x_coord, float y_coord,
                 float display_size) {

  if (!*hold_ptr)
    return;

  int rect_no = *rect_no_ptr;
  SDL_FRect *pixel_storage = *pixel_storage_ptr;

  if (rect_no < (int)display_size) {
    SDL_FRect *new_size =
        realloc(pixel_storage, (rect_no + 1) * sizeof(SDL_FRect));
    if (new_size == NULL) {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error expanding memory");
      *hold_ptr = false;
      return;
    }
    *pixel_storage_ptr = new_size;
    rect_no++;

    (*pixel_storage_ptr)[rect_no - 1].x = x_coord - (pixel_size / 2.0f);
    (*pixel_storage_ptr)[rect_no - 1].y = y_coord - (pixel_size / 2.0f);
    (*pixel_storage_ptr)[rect_no - 1].w = pixel_size;
    (*pixel_storage_ptr)[rect_no - 1].h = pixel_size;

    *rect_no_ptr = rect_no;
  }
}
