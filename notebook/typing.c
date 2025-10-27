#include "typing.h"
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
void typing(Buffer *buffer, const char *typed_char) {
  // Returns text in the memory
  if (typed_char == NULL) {
    SDL_Log("Error");
  }
  if (buffer->cursor + strlen(typed_char) < sizeof(buffer->buffer) - 1) {
    memcpy(&buffer->buffer[buffer->cursor], typed_char,
           strlen(typed_char)); // Also works without memory copy
    buffer->cursor += strlen(typed_char);
  }
}
