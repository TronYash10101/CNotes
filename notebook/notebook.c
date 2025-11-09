#include "notebook.h"
#include "SDL3/SDL_log.h"

int text_width, text_height;
char title[] = "Notebook";

int notebook(SDL_Window *notebook_window, SDL_Renderer *notebook_renderer,
             bool *done, SDL_Event *event_ptr) {

  static bool initialized = false;
  static bool istyping = false;
  static int cursor_x = 0;
  static int line_count = 1;
  static int prev_line_count = 1;
  static int curr_line_word_count = 0;
  static SDL_FRect *line_bg_storage = NULL;
  static TTF_Font *font = NULL;
  static TTF_TextEngine *engine = NULL;
  static TTF_Text *word = NULL;
  static LineBuffer line_buffer;
  static WordBuffer curr_word;
  static int text_width, text_height;
  static int line_skip = 30;

  SDL_Window *window = notebook_window;
  SDL_Renderer *renderer = notebook_renderer;

  // initialize once
  if (!initialized) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_Rect notebook_input = {10, 10, 490, 490};
    SDL_SetTextInputArea(window, &notebook_input, 1);

    engine = TTF_CreateRendererTextEngine(renderer);
    if (!engine) {
      SDL_Log("Text engine error");
    }

    float font_size = 30;
    font = TTF_OpenFont("D:/CNotes/notebook/fonts/arial.ttf", font_size);
    if (!font) {
      SDL_Log("Font load error");
    }

    TTF_SetFontSize(font, font_size);
    TTF_SetFontLineSkip(font, line_skip);

    line_bg_storage = malloc(sizeof(SDL_FRect));
    initialized = true;
  }

  SDL_Event event = *event_ptr;

  // --- Handle events (single frame) ---
  switch (event.type) {
  case SDL_EVENT_QUIT:
    *done = true;
    break;
  case SDL_EVENT_KEY_DOWN:
    if (((event.key.mod & SDL_KMOD_LSHIFT) && event.key.key == SDLK_I) ||
        event.key.key == SDLK_I) {
      istyping = true;
      SDL_StartTextInput(window);
    } else if (event.key.key == SDLK_ESCAPE) {
      istyping = false;
      SDL_StopTextInput(window);
    } else if (event.key.key == SDLK_RETURN) {
      typing(&line_buffer, &curr_word, &cursor_x, "\n", &line_count,
             &curr_line_word_count);
    } else if (event.key.key == SDLK_BACKSPACE) {
      typing(&line_buffer, &curr_word, &cursor_x, "\b", &line_count,
             &curr_line_word_count);
    } else if (event.key.key == SDLK_LEFT) {
      typing(&line_buffer, &curr_word, &cursor_x, LEFT_SYMBOL, &line_count,
             &curr_line_word_count);
    } else if (event.key.key == SDLK_RIGHT) {
      typing(&line_buffer, &curr_word, &cursor_x, RIGHT_SYMBOL, &line_count,
             &curr_line_word_count);
    }
    break;

  case SDL_EVENT_TEXT_INPUT: {
    const char *typed_char = event.text.text;
    typing(&line_buffer, &curr_word, &cursor_x, typed_char, &line_count,
           &curr_line_word_count);
    break;
  }
  }

  // --- Rendering ---
  SDL_SetRenderDrawColor(renderer, 12, 12, 12, 255);
  SDL_RenderClear(renderer);

  if (istyping) {
    if (prev_line_count != line_count) {
      SDL_FRect *new_line_bg_storage =
          realloc(line_bg_storage, line_count * sizeof(SDL_FRect));
      if (new_line_bg_storage != NULL) {
        line_bg_storage = new_line_bg_storage;
      } else {
        return 0;
      }
      prev_line_count = line_count;
    }

    if (word) {
      TTF_DestroyText(word);
    }

    word = TTF_CreateText(engine, font, curr_word.buffer, 0);
    TTF_Text *cursor_word =
        TTF_CreateText(engine, font, line_buffer.word_buffer[0].buffer, 0);
    TTF_GetTextSize(cursor_word, &text_width, &text_height);
    render_caret(renderer, text_height, text_width,
                 ((line_skip) * (line_count - 1)));
    TTF_DestroyText(cursor_word);
  }

  if (word) {
    TTF_SetTextColor(word, 255, 255, 255, 255);
    TTF_DrawRendererText(word, 0, 0);
  }

  for (int line_no = 0; line_no < line_count; line_no++) {
    line_bg_storage[line_no].x = 0;
    line_bg_storage[line_no].y = (line_skip) * (line_no + 1);
    line_bg_storage[line_no].w = 1920;
    line_bg_storage[line_no].h = 1;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &line_bg_storage[line_no]);
  }

  SDL_RenderPresent(renderer);

  return *done;
}
