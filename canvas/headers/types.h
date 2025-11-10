#ifndef TYPES
#define TYPES
#define SCALE_X(default_width) default_width * (1420.0f / 1920.0f)
#include "SDL3/SDL.h"
typedef enum {
  TOOL_NONE,
  TOOL_PEN,
  TOOL_LINE,
  TOOL_ERASER,
  TOOL_RECTANGLE,
} ToolType;

typedef struct {
  ToolType selected_tool;
} ToolSelected;

typedef struct {
  SDL_FRect white;
  SDL_FRect red;
  SDL_FRect green;
  SDL_FRect blue;
} Color_Picker_Rects;

typedef enum { WHITE, RED, GREEN, BLUE } Colors;

#define Offset_X 500
#define Offset_Y 0

#endif // !TYPES
