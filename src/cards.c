#include <render.h>
#include <texture.h>
#include <thirdparty.h>
#include <cards.h>
#include <window.h>
#include <render.h>

void render_cards(window_t* window, texture_map_t* t_map)
{
	/* In Solitare we recognize 4 diffrent piles:
		*  1. Tableau - Seven piles that make up the main table.
		*  2. Foundation - Four piles on which a whole suit or sequence must be built up. 
		*  3. Stock (or Hand) - If the entire pack is not laid out in a tableau at the 
		*                       beginning of a game, the remaining cards form the stock pile 
		*                       from which additional cards are brought into play according 
		*                       to the rules.
		*  4. The Talon (or Waste) - Cards from the stock pile that have no place in the tableau
		*                            or on foundations 
		*/

	render_tableau_pile(window, t_map);
	render_foundation_pile(window, t_map);
	render_stock_pile(window, t_map);
	render_talon_pile(window, t_map);
}

void render_tableau_pile(window_t* window, texture_map_t* t_map)
{
}

void render_foundation_pile(window_t* window, texture_map_t* t_map)
{
}

void render_stock_pile(window_t* window, texture_map_t* t_map)
{
	int x_pos = (int)round(window->width * 0.05);  // 5% margin
	int y_pos = (int)round(window->width * 0.025); // 2.5% margin

	render_texture_as_image_resized(window, t_map->card_back, x_pos, y_pos, CARD_SIZE);
}

void render_talon_pile(window_t* window, texture_map_t* t_map)
{
}

card_texture_t* create_card_texture_from_card_t(window_t* window, card_t card)
{
	card_texture_t* card_texture = calloc(1, sizeof(card_texture_t));
	card_texture->path = card.path;
	memcpy(card_texture->id, card.id, 4);

	card_texture->card_texture = create_texture(window, card.path);
	if (card_texture->card_texture == NULL)
	{
		printf("runtime error: couldn't load card texture \'%s\'\n", card.path);
		return NULL;
	}

	return card_texture;
}

void load_all_cards_textures(window_t* window, texture_map_t* t_map)
{
	/* This function basically goes through all the playing
	 * cards defined in `all_cards` and load's them to the 
	 * `t_map->cards` array */
	printf("%p\n", t_map);
	t_map->cards = calloc(52, sizeof(card_texture_t*));

	for (int i = 0; i < 52; i++)
	{
		card_t current_card = all_cards[i];

		card_texture_t* card_texture = 
				create_card_texture_from_card_t(window, current_card);

		// TODO: add better handling of card loading error 
		if (card_texture == NULL)
		{
			texture_map_destroy(t_map);
			window_destroy(window);
			quit_thirdparty();
		}

		t_map->cards[i] = card_texture;
		printf("loaded card: id=%s, path=%s, texture=%p\n", card_texture->id, card_texture->path, card_texture->card_texture);
	}
}
