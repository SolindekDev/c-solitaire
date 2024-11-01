#include <core.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

#include <texture.h>
#include <window.h>

bool texture_collect_image_data(texture_t* texture)
{
	int _r = SDL_QueryTexture(texture->pure_texture, &texture->format, &texture->access, 
								   							&texture->width, &texture->height);

	if (_r != 0)
	{
		printf("runtime error: couldn't collect data texture at \'%s\'\n", texture->path_image);
		return false;
	}

	return true;
}

texture_t* create_texture_structure(SDL_Texture* sdl_texture, char* path)
{
	texture_t* texture = calloc(1, sizeof(texture_t));
	texture->pure_texture = sdl_texture;
	texture->path_image   = path;

	if (texture_collect_image_data(texture) == false)
	{
		SDL_DestroyTexture(texture->pure_texture);
		free(texture);
		return NULL;
	}

	return texture;
}

texture_t* create_texture(window_t* w, char* path_image)
{
	/* Create a SDL_Surface variable and try to load a image to it */
	SDL_Surface* image = NULL;

	if ((image = IMG_Load(path_image)) == NULL)
	{
		printf("runtime error: texture at \'%s\' doesn't exists\n", path_image);
		return NULL;
	}

	/* Create a texture from the loaded surface */
	SDL_Texture* texture = NULL;

	if ((texture = SDL_CreateTextureFromSurface(w->sdl_renderer, image)) == NULL)
	{
		printf("runtime error: couldn't create a texture from loaded image surface at \'%s\'\n", path_image);
		return NULL;
	}

	SDL_FreeSurface(image);
	return create_texture_structure(texture, path_image);
}

void texture_destroy(texture_t* texture)
{
	SDL_DestroyTexture(texture->pure_texture);
	free(texture);
}

texture_map_t* create_texture_map(window_t* w)
{
	texture_map_t* t_map = calloc(1, sizeof(texture_map_t));
	t_map->card_back  = create_texture(w, CARD_BACK_PATH);
	t_map->card_blank = create_texture(w, CARD_BLANK_PATH);

	// TODO: load_all_cards_textures as an another thread 
	load_all_cards_textures(w, t_map);
	return t_map;
}

void texture_map_destroy(texture_map_t* t_map)
{
	texture_destroy(t_map->card_back);

	for (int i = 0; i < 52; i++)
	{
		texture_destroy(t_map->cards[i]->card_texture);
		free(t_map->cards[i]);
	}

	free(t_map->cards);
	free(t_map);
}