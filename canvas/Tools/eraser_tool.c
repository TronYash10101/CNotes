#include "eraser_tool.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
int eraser_size = 5;

void point_eraser(Pixel **pixel_storage_ptr, float mouse_x, float mouse_y,
                  int rect_no) {

  // getting double pointer as later realloc has to be used for moving erased
  // memory to stack
  Pixel *pixel_storage = *pixel_storage_ptr;

  // general equation of circle to know if point is inside or outside
  for (int i = 0; i < rect_no; i++) {
    Pixel *curr_point = &pixel_storage[i];
    int x = curr_point->pixel.x;
    int y = curr_point->pixel.y;
    float S =
        x * x + y * y - (2 * mouse_x * curr_point->pixel.x) -
        (2 * mouse_y * curr_point->pixel.y) +
        (mouse_x * mouse_x + mouse_y * mouse_y - eraser_size * eraser_size);
    if (S <= 0) {
      SDL_Log("Point inside or on");
      curr_point->visible = false;
    }
  }
}
