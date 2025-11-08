#include "SDL3/SDL.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_textengine.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "typing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NOTEBOOK
#define NOTEBOOK

extern char title[];
int notebook(SDL_Window *notebook_window, SDL_Renderer *notebook_renderer,
             bool *done, SDL_Event *event_ptr);
#endif // !NOTEBOOK
