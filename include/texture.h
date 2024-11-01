#ifndef TEXTURE_H
#define TEXTURE_H

#include <core.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <window.h>
#include <cards.h>

typedef struct __texture_t {
    SDL_Texture* pure_texture;
    char* path_image;

    /* texture data */
    int width, height, access;
    unsigned int format;
} texture_t;

typedef struct __card_texture_t card_texture_t;

typedef struct __texture_map_t {
    card_texture_t** cards;
    texture_t* card_blank;
    texture_t* card_back;
} texture_map_t;

texture_t* create_texture(window_t* w, char* path_image);
void texture_destroy(texture_t* texture);

texture_map_t* create_texture_map(window_t* w);
void texture_map_destroy(texture_map_t* t_map);

#endif /* TEXTURE_H */