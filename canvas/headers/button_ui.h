#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

#ifndef BUTTON_UI
#define BUTTON_UI

void button_ui(SDL_Window *window, SDL_Renderer *renderer,
               SDL_Surface *image_surface, SDL_Texture *texture,
               SDL_FRect srcrect, SDL_FRect b_srcrect, SDL_FRect dstrect);
#endif // !BUTTON_UI
