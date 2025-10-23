#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "line_tool.h"
#include "pen_tool.h"
#include "tools_panel.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define pixel_size 3

int display_height;
int display_width;
char WINDOW_NAME[] = "Canvas";
int rect_no = 0;
int line_no = 0;
bool done = false;
bool hold = false;

char pencil_file[] = "D:/CNotes/canvas/UI/assets/pencil_texture.png";
char line_file[] = "D:/CNotes/canvas/UI/assets/line_texture.png";

typedef enum {
  TOOL_NONE,
  TOOL_PEN,
  TOOL_LINE,
} ToolType;

typedef struct {
  ToolType selected_tool;
} ToolSelected;

int main(int argc, char *argv[]) {
  SDL_FRect *pixel_storage = NULL;
  Line *line_storage = NULL;

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
  SDL_Surface *line_surface = IMG_Load(line_file);
  SDL_Texture *pencil_texture =
      SDL_CreateTextureFromSurface(renderer, pencil_surface);
  SDL_Texture *line_texture =
      SDL_CreateTextureFromSurface(renderer, line_surface);
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
            event.button.x >= pen_button.bg_rcrect.x &&
            event.button.x <= pen_button.bg_rcrect.x + pen_button.bg_rcrect.w &&
            event.button.y >= pen_button.bg_rcrect.y &&
            event.button.y <= pen_button.bg_rcrect.y + pen_button.bg_rcrect.h) {
          current_tool.selected_tool = TOOL_PEN;
          SDL_Log("Pen clicked");
        } else if (event.button.button == SDL_BUTTON_LEFT &&
                   event.button.x >= line_button.bg_rcrect.x &&
                   event.button.x <=
                       line_button.bg_rcrect.x + line_button.bg_rcrect.w &&
                   event.button.y >= line_button.bg_rcrect.y &&
                   event.button.y <=
                       line_button.bg_rcrect.y + line_button.bg_rcrect.h) {

          current_tool.selected_tool = TOOL_LINE;
          SDL_Log("line clicked");
        } else {
          current_tool.selected_tool = TOOL_NONE;
        }
        break;
      case SDL_EVENT_MOUSE_BUTTON_UP:
        hold = false;
        break;
      case SDL_EVENT_MOUSE_MOTION:
        if (hold && current_tool.selected_tool == TOOL_PEN) {
          pencil_tool(renderer, &hold, &rect_no, &pixel_storage, event.motion.x,
                      event.motion.y, (float)(display_width * display_height));
        } else if (hold && current_tool.selected_tool == TOOL_LINE) {
          line_tool(&line_storage, &line_no, event.button.x, event.button.y);
        }

        if (hold && line_no > 0) {
          (line_storage)[line_no - 1].x2 = event.motion.x;
          (line_storage)[line_no - 1].y2 = event.motion.y;
        }
        break;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    tool_panel(window, renderer, pencil_surface, line_surface, pencil_texture,
               line_texture, &done);
    if (rect_no > 0) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderFillRects(renderer, pixel_storage, rect_no);
    }
    if (line_no > 0) {
      for (int i = 0; i < line_no; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderLine(renderer, (line_storage)[i].x1, (line_storage)[i].y1,
                       (line_storage)[i].x2, (line_storage)[i].y2);
      }
    }
    SDL_RenderPresent(renderer);
  }

  free(pixel_storage);
  free(line_storage);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
