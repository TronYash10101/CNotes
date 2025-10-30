#ifndef TYPES
#define TYPES

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

#endif // !TYPES
