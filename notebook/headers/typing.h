#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_textengine.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "SDL3/SDL_timer.h"
#include <SDL3/SDL.h>
#include <stdint.h>
#include <stdio.h>
typedef struct {
  char buffer[1024];
  int cursor;
} Buffer;

#ifndef TYPING
#define TYPING

#define CARET_HEIGHT 20
#define CARET_WIDTH 2

void render_caret(SDL_Renderer *renderer, float cursor_h, float x, float y);
void typing(Buffer *buffer, const char *typed_char);
#endif // !TYPING
