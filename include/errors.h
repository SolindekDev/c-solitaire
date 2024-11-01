#ifndef ERRORS_H
#define ERRORS_H

#include <core.h>
#include <SDL2/SDL.h>

#define err_CREATE_WINDOW "Couldn't create a window. SDL ERROR"

#define EXIT_WITH_ERROR(m) ({        \
        printf("error: %s", m);      \
        return EXIT_FAILURE;         \
    })                               \

#define EXIT_WITH_ERROR_SDL(m) ({             \
        printf("error: %s\n", m);             \
        printf("sdl: %s\n", SDL_GetError());  \
        return EXIT_FAILURE;                  \
    })                                        \

#endif /* ERRORS_H */