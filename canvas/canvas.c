#include "canvas.h"
#include "SDL3/SDL_log.h"

char WINDOW_NAME[] = "Canvas";

int pixel_no = 0;
int rect_no = 0;
int line_no = 0;

static bool hold = false;
float hover_x = 0.0f;
float hover_y = 0.0f;

char pencil_file[] = "D:/CNotes/canvas/UI/assets/pencil_texture.png";
char line_file[] = "D:/CNotes/canvas/UI/assets/line_texture.png";
char eraser_file[] = "D:/CNotes/canvas/UI/assets/eraser_texture.png";
char rectangle_file[] = "D:/CNotes/canvas/UI/assets/rectangle_texture.png";

int display_height, display_width;

void log_tool(ToolSelected *current_tool) {

  ToolType tool = current_tool->selected_tool;
  switch (tool) {
  case TOOL_LINE:
    printf("line_tool\n");
    break;
  case TOOL_RECTANGLE:
    printf("rectangle_tool\n");
    break;
  case TOOL_ERASER:
    printf("eraser_tool\n");
    break;
  case TOOL_PEN:
    printf("pen_tool\n");
    break;
  case TOOL_NONE:
    printf("none_tool\n");
    break;
  }
}

bool check_bound(Button_Pos button, float click_x, float click_y) {
  bool in_bound = false;
  if (click_x >= button.bg_rcrect.x &&
      click_x <= button.bg_rcrect.x + button.bg_rcrect.w &&
      click_y >= button.bg_rcrect.y &&
      click_y <= button.bg_rcrect.y + button.bg_rcrect.h) {
    in_bound = true;
  }
  return in_bound;
}
int canvas(SDL_Window *window, SDL_Renderer *renderer, bool *done,
           SDL_Event *event_ptr, Pixel **pixel_storage, Line **line_storage,
           Rectangle **rectangle_storage, SDL_Texture *pencil_texture,
           SDL_Texture *line_texture, SDL_Texture *eraser_texture,
           SDL_Texture *rectangle_texture) {
  /* Pixel *pixel_storage = *pixel_storage_ptr;
  Line *line_storage = *line_storage_ptr;
  Rectangle *rectangle_storage = *rectangle_storage_ptr; */

  static ToolSelected current_tool = {.selected_tool = TOOL_NONE};

  SDL_GetWindowSizeInPixels(window, &display_width, &display_height);

  SDL_Event event = *event_ptr;

  switch (event.type) {
  case SDL_EVENT_QUIT:
    *done = true;
    break;

  case SDL_EVENT_MOUSE_BUTTON_DOWN:
    if (event.button.button == SDL_BUTTON_LEFT) {
      hold = true;
    }
    if (event.button.button == SDL_BUTTON_LEFT &&
        check_bound(pen_button, event.button.x, event.button.y)) {
      current_tool.selected_tool = TOOL_PEN;
      SDL_Log("Pen clicked");
    } else if (event.button.button == SDL_BUTTON_LEFT &&
               check_bound(line_button, event.button.x, event.button.y)) {
      current_tool.selected_tool = TOOL_LINE;
      SDL_Log("line clicked");
    } else if (event.button.button == SDL_BUTTON_LEFT &&
               check_bound(eraser_button, event.button.x, event.button.y)) {
      current_tool.selected_tool = TOOL_ERASER;
      SDL_Log("eraser clicked");
    } else if (event.button.button == SDL_BUTTON_LEFT &&
               check_bound(rectangle_button, event.button.x, event.button.y)) {
      current_tool.selected_tool = TOOL_RECTANGLE;
      SDL_Log("rectangle clicked");
    }

    if (!check_bound(line_button, event.button.x, event.button.y) && hold &&
        current_tool.selected_tool == TOOL_LINE) {
      line_tool(line_storage, &line_no, event.button.x, event.button.y);
    }
    if (!check_bound(rectangle_button, event.button.x, event.button.y) &&
        hold && current_tool.selected_tool == TOOL_RECTANGLE) {
      rectangle_tool(rectangle_storage, event.button.x, event.button.y,
                     &rect_no);
    }
    break;

  case SDL_EVENT_MOUSE_BUTTON_UP:
    hold = false;
    break;

  case SDL_EVENT_MOUSE_MOTION:
    hover_x = event.motion.x;
    hover_y = event.motion.y;
    if (!check_bound(pen_button, event.motion.x, event.motion.y) && hold &&
        current_tool.selected_tool == TOOL_PEN) {
      pencil_tool(renderer, &hold, &pixel_no, pixel_storage, event.motion.x,
                  event.motion.y, (float)(display_width * display_height));
    } else if (!check_bound(eraser_button, event.motion.x, event.motion.y) &&
               hold && current_tool.selected_tool == TOOL_ERASER) {
      point_eraser(pixel_storage, event.motion.x, event.motion.y, pixel_no);
      line_eraser(line_storage, event.motion.x, event.motion.y, line_no);
      rectangle_eraser(rectangle_storage, rect_no, event.motion.x,
                       event.motion.y);
    }
    if (!check_bound(line_button, event.motion.x, event.motion.y) &&
        current_tool.selected_tool == TOOL_LINE && hold && line_no > 0) {
      (*line_storage)[line_no - 1].x2 = event.motion.x;
      (*line_storage)[line_no - 1].y2 = event.motion.y;
    }
    if (!check_bound(rectangle_button, event.motion.x, event.motion.y) &&
        current_tool.selected_tool == TOOL_RECTANGLE && hold && rect_no > 0) {
      (*rectangle_storage)[rect_no - 1].Rectangle.w =
          event.motion.x - (*rectangle_storage)[rect_no - 1].Rectangle.x;
      (*rectangle_storage)[rect_no - 1].Rectangle.h =
          event.motion.y - (*rectangle_storage[rect_no - 1]).Rectangle.y;
    }
    break;

  case SDL_EVENT_KEY_DOWN:
    if (event.key.key == SDLK_ESCAPE) {
      current_tool.selected_tool = TOOL_NONE;
    }
    break;
  }

  tool_panel(window, renderer, pencil_texture, line_texture, eraser_texture,
             rectangle_texture, done, &hover_x, &hover_y, &current_tool);

  if (pixel_no > 0) {
    for (int i = 0; i < pixel_no; i++) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      if ((*pixel_storage)[i].visible)
        SDL_RenderFillRect(renderer, &(*pixel_storage)[i].pixel);
    }
  }

  if (rect_no > 0) {
    for (int i = 0; i < rect_no; i++) {
      if ((*rectangle_storage)[i].visible) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderRect(renderer, &(*rectangle_storage)[i].Rectangle);
      }
    }
  }

  if (line_no > 0) {
    for (int i = 0; i < line_no; i++) {
      if ((*line_storage)[i].visible) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderLine(renderer, (*line_storage)[i].x1, (*line_storage)[i].y1,
                       (*line_storage)[i].x2, (*line_storage)[i].y2);
      }
    }
  }

  return *done;
}
