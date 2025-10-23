#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#ifndef TOOLS_PANEL
#define TOOLS_PANEL

typedef struct {
  SDL_FRect srcrect;
  SDL_FRect drcrect;
  SDL_FRect bg_rcrect;

} Button_Pos;

extern char title[];
extern char pencil_file[];
extern char line_file[];

extern Button_Pos pen_button;
extern Button_Pos line_button;
extern void tool_panel(SDL_Window *window, SDL_Renderer *renderer,
                       SDL_Surface *pencil_surface, SDL_Surface *line_surface,
                       SDL_Texture *pencil_texture, SDL_Texture *line_texture,
                       bool *done);

#endif // !TOOLS_PANEL
