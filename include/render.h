#ifndef RENDER_H
#define RENDER_H

#include <texture.h>
#include <window.h>

void render_texture_as_background(window_t* w, texture_t* texture);
void render_texture_as_image(window_t* w, texture_t* texture, int x, int y);
void render_texture_as_image_resized(window_t* _w, texture_t* texture, int x, int y, int w, int h);

#endif /* RENDER_H */