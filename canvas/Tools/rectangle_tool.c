#include "rectangle_tool.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
void rectangle_tool(Rectangle **rectangle_storage_ptr, float rect_x,
                    float rect_y, int *rect_no_ptr, SDL_Color color) {
  int rect_no = *rect_no_ptr;

  Rectangle *new_rectangle_storage =
      realloc(*rectangle_storage_ptr, (rect_no + 1) * sizeof(Rectangle));
  if (new_rectangle_storage == NULL) {
    SDL_Log("Failed to realloc rectangle storage");
    return;
  }

  *rectangle_storage_ptr = new_rectangle_storage;

  *rect_no_ptr = rect_no + 1;
  (*rectangle_storage_ptr)[rect_no].Rectangle.x = rect_x;
  (*rectangle_storage_ptr)[rect_no].Rectangle.y = rect_y;
  (*rectangle_storage_ptr)[rect_no].Rectangle.w = 0;
  (*rectangle_storage_ptr)[rect_no].Rectangle.h = 0;
  (*rectangle_storage_ptr)[rect_no].visible = true;
  (*rectangle_storage_ptr)[rect_no].color = color;
}
