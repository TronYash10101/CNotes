#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "eraser_tool.h"
#include "line_tool.h"
#include "pen_tool.h"
#include "rectangle_tool.h"
#include "tools_panel.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define pixel_size 3

int display_height;
int display_width;
char WINDOW_NAME[] = "Canvas";
int pixel_no = 0;
int rect_no = 0;
int line_no = 0;
bool done = false;
bool hold = false;

char pencil_file[] = "D:/CNotes/canvas/UI/assets/pencil_texture.png";
char line_file[] = "D:/CNotes/canvas/UI/assets/line_texture.png";
char eraser_file[] = "D:/CNotes/canvas/UI/assets/eraser_texture.png";
char rectangle_file[] = "D:/CNotes/canvas/UI/assets/rectangle_texture.png";

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

int main(int argc, char *argv[]) {
  Pixel *pixel_storage = NULL;
  Line *line_storage = NULL;
  Rectangle *rectangle_storage = NULL;

  ToolSelected current_tool = {.selected_tool = TOOL_NONE};

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return -1;
  }

  SDL_Window *window = SDL_CreateWindow(
      WINDOW_NAME, 1920, 1080, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
  if (!window) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  SDL_Surface *pencil_surface = IMG_Load(pencil_file);
  SDL_Texture *pencil_texture =
      SDL_CreateTextureFromSurface(renderer, pencil_surface);
  SDL_Surface *line_surface = IMG_Load(line_file);
  SDL_Texture *line_texture =
      SDL_CreateTextureFromSurface(renderer, line_surface);
  SDL_Surface *eraser_surface = IMG_Load(eraser_file);
  SDL_Texture *eraser_texture =
      SDL_CreateTextureFromSurface(renderer, eraser_surface);
  SDL_Surface *rectangle_surface = IMG_Load(rectangle_file);
  SDL_Texture *rectangle_texture =
      SDL_CreateTextureFromSurface(renderer, rectangle_surface);

  SDL_GetWindowSizeInPixels(window, &display_width, &display_height);

  while (!done) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        done = true;
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
                   check_bound(rectangle_button, event.button.x,
                               event.button.y)) {
          current_tool.selected_tool = TOOL_RECTANGLE;
          SDL_Log("rectangle clicked");
        }
        // Initial rendering for line and rectangle
        if (!check_bound(line_button, event.button.x, event.button.y) && hold &&
            current_tool.selected_tool == TOOL_LINE) {
          line_tool(&line_storage, &line_no, event.button.x, event.button.y);
        }
        if (!check_bound(rectangle_button, event.button.x, event.button.y) &&
            hold && current_tool.selected_tool == TOOL_RECTANGLE) {
          rectangle_tool(&rectangle_storage, event.button.x, event.button.y,
                         &rect_no);
        }

        break;
      case SDL_EVENT_MOUSE_BUTTON_UP:
        hold = false;
        break;
      case SDL_EVENT_MOUSE_MOTION:
        if (!check_bound(pen_button, event.motion.x, event.motion.y) && hold &&
            current_tool.selected_tool == TOOL_PEN) {
          pencil_tool(renderer, &hold, &pixel_no, &pixel_storage,
                      event.motion.x, event.motion.y,
                      (float)(display_width * display_height));
        } else if (!check_bound(eraser_button, event.motion.x,
                                event.motion.y) &&
                   hold && current_tool.selected_tool == TOOL_ERASER) {
          point_eraser(&pixel_storage, event.motion.x, event.motion.y,
                       pixel_no);
          line_eraser(&line_storage, event.motion.x, event.motion.y, line_no);
          rectangle_eraser(rectangle_storage, rect_no, event.motion.x,
                           event.motion.y);
        }
        if (!check_bound(line_button, event.motion.x, event.motion.y) &&
            current_tool.selected_tool == TOOL_LINE && hold && line_no > 0) {
          (line_storage)[line_no - 1].x2 = event.motion.x;
          (line_storage)[line_no - 1].y2 = event.motion.y;
        }
        if (!check_bound(rectangle_button, event.motion.x, event.motion.y) &&
            current_tool.selected_tool == TOOL_RECTANGLE && hold &&
            rect_no > 0) {
          // SDL_Log("%f", rectangle_storage->Rectangle.x);
          (rectangle_storage)[rect_no - 1].Rectangle.w =
              event.motion.x - rectangle_storage[rect_no - 1].Rectangle.x;
          (rectangle_storage)[rect_no - 1].Rectangle.h =
              event.motion.y - rectangle_storage[rect_no - 1].Rectangle.y;
        }

        break;
      }
    }
    // log_tool(&current_tool);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    tool_panel(window, renderer, pencil_surface, line_surface, pencil_texture,
               line_texture, eraser_surface, eraser_texture, rectangle_surface,
               rectangle_texture, &done);

    if (pixel_no > 0) {
      for (int i = 0; i < pixel_no; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        if (pixel_storage[i].visible) {
          SDL_RenderFillRect(renderer, &pixel_storage[i].pixel);
          // SDL_Log("Rendering %d pixels", rect_no);
        }
      }
    }
    if (rect_no > 0) {
      for (int i = 0; i < rect_no; i++) {
        if (rectangle_storage[i].visible) {
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
          SDL_RenderRect(renderer, &rectangle_storage[i].Rectangle);
        }
      }
    }
    if (line_no > 0) {
      for (int i = 0; i < line_no; i++) {
        if (line_storage[i].visible) {
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
          SDL_RenderLine(renderer, (line_storage)[i].x1, (line_storage)[i].y1,
                         (line_storage)[i].x2, (line_storage)[i].y2);
        }
      }
    }
    SDL_RenderPresent(renderer);
  }

  free(pixel_storage);
  free(line_storage);
  free(rectangle_storage);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
