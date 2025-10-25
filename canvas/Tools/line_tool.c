#include "line_tool.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void line_tool(Line **line_storage, int *line_no_ptr, float x1, float y1) {
  int line_no = *line_no_ptr;
  Line *new_line_storage = realloc(*line_storage, (line_no + 1) * sizeof(Line));

  if (new_line_storage == NULL) {
    return;
  }
  *line_storage = new_line_storage;
  *line_no_ptr += 1;
  Line *current_line = &new_line_storage[line_no];
  current_line->x1 = x1;
  current_line->y1 = y1;
  current_line->x2 = x1; // Initialize endpoint to start point (rubber banding)
  current_line->y2 = y1;
  current_line->visible = true;
}
