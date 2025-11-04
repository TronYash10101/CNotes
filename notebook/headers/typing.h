#include "SDL3/SDL.h"
#include "SDL3/SDL_timer.h"
#include "SDL3_ttf/SDL_textengine.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <SDL3/SDL.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
  char buffer[500];
} WordBuffer;

typedef struct {
  WordBuffer word_buffer[1];
} LineBuffer;

typedef struct {
  LineBuffer word_buffer[1024];
} ParagraphBuffer;

#ifndef TYPING
#define TYPING

#define UP_SYMBOL "<1>"
#define DOWN_SYMBOL "<2>"
#define LEFT_SYMBOL "<3>"
#define RIGHT_SYMBOL "<4>"

#define CARET_HEIGHT 20
#define CARET_WIDTH 2

void render_caret(SDL_Renderer *renderer, float cursor_h, float cursor_x,
                  float cursor_y);

void typing(LineBuffer *line_buffer, WordBuffer *curr_word, int *cursor_x,
            const char *typed_char, int *word_count, int *curr_line_word_count);
#endif // !TYPING
