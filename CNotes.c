#include "CNotes.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"
#include "canvas.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

bool done = false;

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  Pixel *pixel_storage = NULL;
  Line *line_storage = NULL;
  Rectangle *rectangle_storage = NULL;

  SDL_Window *parent_window = SDL_CreateWindow(
      "CNotes", 1920, 1080, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
  SDL_Renderer *parent_renderer = SDL_CreateRenderer(parent_window, NULL);
  // SDL_Renderer *notebook_renderer = SDL_CreateRenderer(parent_window, NULL);

  SDL_Surface *pencil_surface = IMG_Load(pencil_file);
  SDL_Texture *pencil_texture =
      SDL_CreateTextureFromSurface(parent_renderer, pencil_surface);
  SDL_Surface *line_surface = IMG_Load(line_file);
  SDL_Texture *line_texture =
      SDL_CreateTextureFromSurface(parent_renderer, line_surface);
  SDL_Surface *eraser_surface = IMG_Load(eraser_file);
  SDL_Texture *eraser_texture =
      SDL_CreateTextureFromSurface(parent_renderer, eraser_surface);
  SDL_Surface *rectangle_surface = IMG_Load(rectangle_file);
  SDL_Texture *rectangle_texture =
      SDL_CreateTextureFromSurface(parent_renderer, rectangle_surface);

  SDL_Texture *canvas_texture =
      SDL_CreateTexture(parent_renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, 1420, 1080);
  SDL_Texture *notebook_texture =
      SDL_CreateTexture(parent_renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, 500, 1080);

  // Each frame:
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {

      case SDL_EVENT_QUIT:
        done = true;
        break;
      }
      SDL_SetRenderTarget(parent_renderer, canvas_texture);
      SDL_RenderClear(parent_renderer);
      canvas(parent_window, parent_renderer, &done, &event, &pixel_storage,
             &line_storage, &rectangle_storage, pencil_texture, line_texture,
             eraser_texture, rectangle_texture);

      SDL_SetRenderTarget(parent_renderer, notebook_texture);
      SDL_RenderClear(parent_renderer);
      notebook(parent_window, parent_renderer, &done, &event);

      SDL_SetRenderTarget(parent_renderer, NULL);
      SDL_SetRenderDrawColor(parent_renderer, 18, 18, 18, 255);
      SDL_RenderClear(parent_renderer);

      SDL_FRect dst = {500, 0, 1420, 1080};
      SDL_FRect dst_n = {0, 0, 500, 1080};

      SDL_RenderTexture(parent_renderer, notebook_texture, NULL, &dst_n);
      SDL_RenderTexture(parent_renderer, canvas_texture, NULL, &dst);

      SDL_RenderPresent(parent_renderer);
    }
  }

  free(pixel_storage);
  free(line_storage);
  free(rectangle_storage);

  SDL_DestroyTexture(pencil_texture);
  SDL_DestroyTexture(line_texture);
  SDL_DestroyTexture(eraser_texture);
  SDL_DestroyTexture(rectangle_texture);
  SDL_DestroyTexture(canvas_texture);
  SDL_DestroyTexture(notebook_texture);

  SDL_DestroyRenderer(parent_renderer);
  SDL_DestroyWindow(parent_window);
  SDL_DestroySurface(pencil_surface);
  SDL_DestroySurface(line_surface);
  SDL_DestroySurface(eraser_surface);
  SDL_DestroySurface(rectangle_surface);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
