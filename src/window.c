#include <SDL2/SDL_events.h>
#include <core.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <thirdparty.h>
#include <window.h>

#define WINDOW_FLAG (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)

bool create_sdl_window_and_renderer(window_t* window)
{
  window->sdl_window = 
      SDL_CreateWindow(window->title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       window->width, window->height, WINDOW_FLAG);

  if (window->sdl_window == NULL)
    return false;

  window->sdl_renderer =
      SDL_CreateRenderer(window->sdl_window, -1, SDL_RENDERER_ACCELERATED);

  if (window->sdl_renderer == NULL)
    return false;

  return true;
}

static int event_watcher(void* data, SDL_Event* event)
{
  /* This function is going to constantly update 
   * the window properties into the structure like
   * resizing etc. */
  
  window_t* window = (window_t*)data;

  if (event->type == SDL_WINDOWEVENT) 
  {
    if (event->window.event == SDL_WINDOWEVENT_RESIZED      ||
        event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED || 
        event->window.event == SDL_WINDOWEVENT_MINIMIZED    ||
        event->window.event == SDL_WINDOWEVENT_MAXIMIZED)
    {
      window->width  = event->window.data1;
      window->height = event->window.data2;
    }
  }

  return 0;
}

window_t* create_window(const char* title, int width, int height) 
{
  /* You firstly need to initialize SDL2 */
  if (!is_init_thirdparty())
    return NULL;

  window_t* window = calloc(1, sizeof(window_t));
  window->title = title;
  window->width = width;
  window->height = height;

  if (!create_sdl_window_and_renderer(window)) 
  {
    free(window);
    return NULL;
  }

  SDL_AddEventWatch(event_watcher, window);

  return window;
}

void window_start_fps_measuring(window_t* window)
{
  window->last_tick = clock();
}

void window_measure_fps(window_t* window)
{
  clock_t now = clock();
  window->frames++;

  if (now > (window->last_tick + CLOCKS_PER_SEC)) 
  {
    window->fps = window->frames;
    window->frames = 0;
    window->last_tick = now;
  }
}

bool window_should_exit(window_t* window)
{
  return !window->window_loop;
}

void window_handle_events(window_t* window)
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
        case SDL_QUIT:
            window->window_loop = true;
            break;
    }
  }
}

void window_clear_renderer(window_t* window)
{
  SDL_SetRenderDrawColor(window->sdl_renderer, 0, 0, 0, 255);
  SDL_RenderClear(window->sdl_renderer);
}

void window_present(window_t *window)
{
  SDL_RenderPresent(window->sdl_renderer);
}

void window_destroy(window_t *window) 
{
  SDL_DestroyWindow(window->sdl_window);
  SDL_DestroyRenderer(window->sdl_renderer);
  free(window);
}