#include "pen_tool.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void pencil_tool(SDL_Renderer *renderer, bool *hold_ptr, int *rect_no_ptr,
                 Pixel **pixel_storage_ptr, float x_coord, float y_coord,
                 float display_size) {

  if (!*hold_ptr)
    return;

  int rect_no = *rect_no_ptr;
  Pixel *pixel_storage = *pixel_storage_ptr;

  if (rect_no < (int)display_size) {
    Pixel *new_size = realloc(pixel_storage, (rect_no + 1) * sizeof(Pixel));
    if (new_size == NULL) {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error expanding memory");
      *hold_ptr = false;
      return;
    }
    *pixel_storage_ptr = new_size;
    rect_no++;

    (*pixel_storage_ptr)[rect_no - 1].pixel.x = x_coord - (pixel_size / 2.0f);
    (*pixel_storage_ptr)[rect_no - 1].pixel.y = y_coord - (pixel_size / 2.0f);
    (*pixel_storage_ptr)[rect_no - 1].pixel.w = pixel_size;
    (*pixel_storage_ptr)[rect_no - 1].pixel.h = pixel_size;
    (*pixel_storage_ptr)[rect_no - 1].visible = true;

    *rect_no_ptr = rect_no;
  }
}
