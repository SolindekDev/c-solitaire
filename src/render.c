#include <core.h>

#include <SDL2/SDL.h>

#include <render.h>
#include <texture.h>
#include <window.h>

void render_texture_as_background(window_t* w, texture_t* texture)
{
	/* Create a destination rectangle and then render 
	 * the given texture to the screen */
	SDL_Rect dst_rect = { 0, 0, w->width, w->height };
	SDL_RenderCopy( 
			w->sdl_renderer, texture->pure_texture, NULL, &dst_rect );
}

void render_texture_as_image(window_t* w, texture_t* texture, int x, int y)
{
	/* The same thing like in the render_texture_as_background
	 * but we have specified x and y postion  */
	SDL_Rect dst_rect = { x, y, texture->width, texture->height };
	SDL_RenderCopy( 
			w->sdl_renderer, texture->pure_texture, NULL, &dst_rect );
}

void render_texture_as_image_resized(window_t* _w, texture_t* texture, int x, int y, int w, int h)
{
	/* The same thing like in the render_texture_as_image
	 * but we have specified x and y postion */
	SDL_Rect dst_rect = { x, y, w, h };
	SDL_RenderCopy( 
			_w->sdl_renderer, texture->pure_texture, NULL, &dst_rect );
}
