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
char title[] = "Notebook";
int text_width, text_height = 0;
int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  SDL_FRect notebook_area = {0, 0, 500, 500};
  SDL_Rect notebook_input = {10, 10, 490, 490};
  Buffer word_buff;

  bool done = false;
  bool istyping = false;
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

  TTF_Font *font = TTF_OpenFont("D:/CNotes/notebook/fonts/arial.ttf", 48);
  if (font == NULL) {
    SDL_Log("Text engine error");
  }

  TTF_SetFontSize(font, 30.0f);

  // Create a text object
  TTF_Text *myText;
  if (!SDL_SetTextInputArea(window, &notebook_input, 1)) {
    SDL_Log("Error while creating input area");
  };
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
        } else if (event.key.key == SDLK_BACKSPACE && word_buff.cursor > 0) {
          word_buff.cursor -= 1;
          word_buff.buffer[word_buff.cursor] = '\0';
        } else if (event.key.key == SDLK_RETURN) {
          word_buff.buffer[word_buff.cursor] =
              '\n'; // add newline, then move cursor
          word_buff.cursor += 1;
          word_buff.buffer[word_buff.cursor] = '\0'; // always null-terminate
        }
        break;
      case SDL_EVENT_TEXT_INPUT:
        if (istyping) {
          const char *typed_char = event.text.text;
          typing(&word_buff, typed_char);
        }
        break;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    if (istyping) {
      if (myText) {
        TTF_DestroyText(myText);
      }
      myText = TTF_CreateText(engine, font, word_buff.buffer, 0);
      TTF_GetTextSize(myText, &text_width, &text_height);
      render_caret(renderer, text_height, text_width, 5);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    TTF_DrawRendererText(myText, 0, 5);
    // SDL_RenderRect(renderer, &notebook_area);
    SDL_RenderPresent(renderer);
  }
  if (myText) {
    TTF_DestroyText(myText);
  }
  TTF_CloseFont(font);
  TTF_DestroyRendererTextEngine(engine);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
