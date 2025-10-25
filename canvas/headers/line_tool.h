#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

#ifndef LINE_TOOL
#define LINE_TOOL
typedef struct {
  float x1;
  float y1;
  float x2;
  float y2;
  bool visible;
} Line;

extern Uint32 LINE_TOOL_EVENT;
void line_tool(Line **line_storage, int *line_no_ptr, float x1, float y1);
#endif // !LINE_TOOL
