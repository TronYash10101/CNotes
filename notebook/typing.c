#include "typing.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_stdinc.h"
#include <stdio.h>
#include <string.h>

void render_caret(SDL_Renderer *renderer, float cursor_h, float cursor_x,
                  float cursor_y) {
  static float caret_alpha = 0;
  static float last_time = 0;
  float current_time = SDL_GetTicks();

  SDL_FRect caret;
  caret.x = cursor_x;
  caret.y = cursor_y;
  caret.w = CARET_WIDTH;
  caret.h = cursor_h;
  // caret_alpha = ~caret_alpha;
  if ((current_time - last_time) >= 500) {
    caret_alpha = (caret_alpha == 0) ? 255 : 0;
    last_time = current_time;
  }
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, caret_alpha);
  SDL_RenderFillRect(renderer, &caret);
}

void typing(LineBuffer *line_buffer, WordBuffer *curr_word, int *cursor_x,
            const char *typed_char, int *line_count,
            int *curr_line_word_count) {
  static bool left_typing = false;
  static bool right_typing = false;
  if (typed_char == NULL) {
    SDL_Log("Error");
  }

  // Backspace logic
  if (typed_char[0] == '\b') {
    if (*cursor_x > 0) {
      *cursor_x -= 1;
      curr_word->buffer[*cursor_x] = '\0';
    }

    const char *last_newline = strrchr(curr_word->buffer, '\n');
    const char *current_line =
        last_newline ? last_newline + 1 : curr_word->buffer;
    memset(line_buffer, 0, sizeof(*line_buffer));
    strcpy(line_buffer->word_buffer[0].buffer, current_line);

    if (*curr_line_word_count > 0) {
      *curr_line_word_count -= 1;
    } else if (*curr_line_word_count == 0 && *line_count > 1) {
      *line_count -= 1;
    }
    *curr_line_word_count = strlen(current_line);
    SDL_Log("words %d && line no.:- %d", *curr_line_word_count, *line_count);
    return;
  }

  if (strcmp(typed_char, LEFT_SYMBOL) == 0 && *cursor_x > 0) {
    *cursor_x -= 1;
    *curr_line_word_count -= 1;
    line_buffer->word_buffer[0].buffer[*curr_line_word_count] = '\0';
    left_typing = true;
  }

  if (strcmp(typed_char, RIGHT_SYMBOL) == 0 && *cursor_x > 0) {
    line_buffer->word_buffer->buffer[*curr_line_word_count] =
        curr_word->buffer[*cursor_x];
    *cursor_x += 1;
    *curr_line_word_count += 1;
    right_typing = true;
  }
  SDL_Log("%d", left_typing);

  if (strcmp(typed_char, UP_SYMBOL) != 0 &&
      strcmp(typed_char, RIGHT_SYMBOL) != 0 &&
      strcmp(typed_char, LEFT_SYMBOL) != 0 &&
      strcmp(typed_char, DOWN_SYMBOL) != 0) {

    // Left typing
    if (*cursor_x + strlen(typed_char) < sizeof(curr_word->buffer) - 1 &&
        left_typing) {
      memmove(&curr_word->buffer[*cursor_x + 1], &curr_word->buffer[*cursor_x],
              strlen(&curr_word->buffer[*cursor_x]) + 1);
      curr_word->buffer[*cursor_x] = *typed_char;
      const char *last_newline = strrchr(curr_word->buffer, '\n');
      const char *current_line = last_newline ? last_newline + 1 : typed_char;
      line_buffer->word_buffer->buffer[*curr_line_word_count] = *current_line;

      *curr_line_word_count += 1;
      *cursor_x += 1;
      // left_typing = false;
      return;
    }

    // Right typing
    if (*cursor_x + strlen(typed_char) < sizeof(curr_word->buffer) - 1 &&
        right_typing) {
      memmove(&curr_word->buffer[*cursor_x + 1], &curr_word->buffer[*cursor_x],
              strlen(&curr_word->buffer[*cursor_x]) + 1);
      curr_word->buffer[*cursor_x] = *typed_char;
      const char *last_newline = strrchr(curr_word->buffer, '\n');
      const char *current_line = last_newline ? last_newline + 1 : typed_char;
      line_buffer->word_buffer->buffer[*curr_line_word_count] = *current_line;

      *curr_line_word_count += 1;
      *cursor_x += 1;
      // right_typing = false;
      return;
    }
    // Add to buffer on typing
    if (*cursor_x + strlen(typed_char) < sizeof(curr_word->buffer) - 1) {
      memcpy(&curr_word->buffer[*cursor_x], typed_char, strlen(typed_char));
      *cursor_x += strlen(typed_char);
      curr_word->buffer[*cursor_x] = '\0';
    }

    const char *last_newline = strrchr(curr_word->buffer, '\n');
    const char *current_line =
        last_newline ? last_newline + 1 : curr_word->buffer;

    memset(line_buffer, 0, sizeof(*line_buffer));
    strcpy(line_buffer->word_buffer[0].buffer, current_line);
    *curr_line_word_count += 1;

    if (*cursor_x > 0 && curr_word->buffer[*cursor_x - 2] == '\n') {
      *line_count += 1;
      *curr_line_word_count = 0;
    }
    return;
  }
}
