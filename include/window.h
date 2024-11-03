#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include <core.h>

typedef struct __window_t {
    const char* title;
    int width, height;

    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;

    bool window_loop;

    unsigned long frames;
    unsigned long fps;
    clock_t       last_tick;
} window_t;

typedef struct __card_manager_t card_manager_t;

window_t* create_window(const char* title, int width, int height);

void window_start_fps_measuring(window_t* window);
void window_measure_fps(window_t* window);

bool window_should_exit(window_t* window);

void window_handle_events(window_t* window, card_manager_t* card_man);
void window_clear_renderer(window_t* window);
void window_present(window_t* window);

void window_destroy(window_t *window);

#endif /* WINDOW_H */