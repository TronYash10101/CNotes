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

char title[] = "Notebook";
int text_width, text_height;

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  SDL_FRect notebook_area = {0, 0, 500, 500};
  SDL_Rect notebook_input = {10, 10, 490, 490};

  bool done = false;
  bool istyping = false;
  int cursor_x = 0; // actual position of cursor in x
  static int line_count = 1;
  static int curr_line_word_count = 0;

  LineBuffer line_buffer;
  WordBuffer curr_word;
  SDL_Window *window = SDL_CreateWindow(
      title, 1920, 1080, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  if (window == NULL || renderer == NULL) {
    SDL_Log("Could not create window or renderer");
    return -1;
  }

  TTF_TextEngine *engine = TTF_CreateRendererTextEngine(renderer);
  if (engine == NULL) {
    SDL_Log("Text engine error");
  }

  float font_size = 30;
  TTF_Font *font =
      TTF_OpenFont("D:/CNotes/notebook/fonts/arial.ttf", font_size);
  if (font == NULL) {
    SDL_Log("Text engine error");
  }
  TTF_SetFontSize(font, font_size);

  TTF_Text *word;
  TTF_Text *cursor_word;

  if (!SDL_SetTextInputArea(window, &notebook_input, 1)) {
    SDL_Log("Error while creating input area");
  };
  int line_skip = TTF_GetFontLineSkip(font);
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        done = true;
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
          curr_word.buffer[cursor_x] = '\n';
          cursor_x += 1;
          curr_word.buffer[cursor_x] = '\0';
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

      case SDL_EVENT_TEXT_INPUT:;
        const char *typed_char = event.text.text;
        typing(&line_buffer, &curr_word, &cursor_x, typed_char, &line_count,
               &curr_line_word_count);
        break;
      }
    }
    SDL_SetRenderDrawColor(renderer, 18, 18, 18, 0);
    SDL_RenderClear(renderer);
    if (istyping) {
      if (word) {
        TTF_DestroyText(word);
      }
      word = TTF_CreateText(engine, font, curr_word.buffer, 0);
      cursor_word =
          TTF_CreateText(engine, font, line_buffer.word_buffer[0].buffer, 0);
      TTF_GetTextSize(cursor_word, &text_width, &text_height);
      render_caret(renderer, text_height, text_width,
                   (line_skip * (line_count - 1)));
    }
    TTF_DrawRendererText(word, 0, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
  }
  if (word) {
    TTF_DestroyText(word);
  }
  TTF_CloseFont(font);
  TTF_DestroyRendererTextEngine(engine);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
