#include "eraser_tool.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

float eraser_size = 40;
void point_eraser(Pixel **pixel_storage_ptr, float mouse_x, float mouse_y,
                  int pixel_no) {

  // getting double pointer as later realloc has to be used for moving erased
  // memory to stack
  Pixel *pixel_storage = *pixel_storage_ptr;
  int erased = 0;
  // general equation of circle to know if point is inside or outside
  for (int i = 0; i < pixel_no; i++) {
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

void line_eraser(Line **line_storage_ptr, float mouse_x, float mouse_y,
                 int line_no) {
  int erased = 0;
  Line *line_storage = *line_storage_ptr;

  for (int i = 0; i < line_no; i++) {
    Line *curr_point = &line_storage[i];
    if (!curr_point->visible)
      continue;

    // Define your variables with your naming style
    float i1 = curr_point->x1;
    float j1 = curr_point->y1;
    float i2 = curr_point->x2;
    float j2 = curr_point->y2;

    float px = mouse_x;
    float py = mouse_y;

    // Vector math (AP and AB)
    float A = px - i1;
    float B = py - j1;
    float C = i2 - i1;
    float D = j2 - j1;

    // Dot product and segment length
    float dot = (A * C) + (B * D);
    float len_sq = (C * C) + (D * D);
    if (len_sq == 0)
      continue; // Avoid division by zero

    // Projection ratio (t) along the segment
    float t = dot / len_sq;

    // Clamp t between 0 and 1 (so projection stays on the segment)
    if (t < 0.0f)
      t = 0.0f;
    else if (t > 1.0f)
      t = 1.0f;

    // Find nearest point on the segment
    float xx = i1 + t * C;
    float yy = j1 + t * D;

    // Compute true distance from eraser to that point
    float dx = px - xx;
    float dy = py - yy;
    float dist = sqrtf(dx * dx + dy * dy);

    // Erase if within eraser radius
    if (dist < eraser_size) {
      curr_point->visible = false;
      erased++;
    }
  }

  if (erased > 0) {
    SDL_Log("Erased %d lines near (%.2f, %.2f)", erased, mouse_x, mouse_y);
  }
}
void rectangle_eraser(Rectangle **rectangle_storage_ptr, int rect_no,
                      float mouse_x, float mouse_y) {

  // adds padding to define region of closeness
  Rectangle *rectangle_storage = *rectangle_storage_ptr;
  for (int i = 0; i < rect_no; i++) {
    Rectangle *curr_rect = &rectangle_storage[i];

    if (!curr_rect->visible)
      continue;

    float x1 = curr_rect->Rectangle.x;
    float y1 = curr_rect->Rectangle.y;
    float x2 = curr_rect->Rectangle.x + curr_rect->Rectangle.w;
    float y2 = curr_rect->Rectangle.y + curr_rect->Rectangle.h;

    float min_x = (x1 < x2) ? x1 : x2;
    float max_x = (x1 > x2) ? x1 : x2;
    float min_y = (y1 < y2) ? y1 : y2;
    float max_y = (y1 > y2) ? y1 : y2;

    if (mouse_x >= min_x - eraser_size && mouse_x <= max_x + eraser_size &&
        mouse_y >= min_y - eraser_size && mouse_y <= max_y + eraser_size) {
      curr_rect->visible = false;
    }
  }
}
