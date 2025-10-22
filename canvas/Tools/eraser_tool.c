#include "eraser_tool.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void point_eraser(Pixel **pixel_storage_ptr, float mouse_x, float mouse_y,
                  int rect_no) {

  float eraser_size = 5;
  // getting double pointer as later realloc has to be used for moving erased
  // memory to stack
  Pixel *pixel_storage = *pixel_storage_ptr;
  int erased = 0;
  // general equation of circle to know if point is inside or outside
  for (int i = 0; i < rect_no; i++) {
    Pixel *curr_point = &pixel_storage[i];
    int x = curr_point->pixel.x;
    int y = curr_point->pixel.y;
    float dx = curr_point->pixel.x - mouse_x;
    float dy = curr_point->pixel.y - mouse_y;
    if (dx * dx + dy * dy <= eraser_size * eraser_size) {
      curr_point->visible = false;
      erased++;
    }
  }
  /*   if (erased > 0)
      SDL_Log("Erased %d pixels at (%.2f, %.2f)", erased, mouse_x, mouse_y); */
}
