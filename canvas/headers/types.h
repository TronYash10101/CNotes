#ifndef TYPES
#define TYPES
#define SCALE_X(default_width) default_width * (1420.0f / 1920.0f)

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

#define Offset_X 500
#define Offset_Y 0

#endif // !TYPES
