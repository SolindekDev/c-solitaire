#include <render.h>
#include <texture.h>
#include <thirdparty.h>
#include <cards.h>
#include <window.h>
#include <render.h>
#include <random.h>

void render_cards(window_t* window, texture_map_t* t_map, card_manager_t* card_man)
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

	render_tableau_pile(window, t_map, card_man);
	render_foundation_pile(window, t_map, card_man);
	render_stock_pile(window, t_map, card_man);
	render_talon_pile(window, t_map, card_man);
}

void render_tableau_pile(window_t* window, texture_map_t* t_map, card_manager_t* card_man)
{
	int x_pos = (int)round(window->width * 0.065);  // 6.5% margin

	for (int i = 0; i < 7; i++)
	{
		int y_pos = (int)round(window->height * 0.05) + CARD_SIZE_Y(window); // 2.5% margin + card_size y + 2.5% margin

		for (int j = 0; j < (i + 1); j++)
		{
			card_t card = card_man->tableau[i][j];
			render_texture_as_image_resized(window, t_map->cards[card.i]->card_texture, x_pos, y_pos, CARD_SIZE(window));
			y_pos += 30;
		}
		
		x_pos += CARD_PADDING(window) + CARD_SIZE_X(window);
	}
}

void render_foundation_pile(window_t* window, texture_map_t* t_map, card_manager_t* card_man)
{
	int x_pos = (int)round(window->width  * 0.065); // 6.5% margin
	int y_pos = (int)round(window->height * 0.025); // 2.5% margin

	x_pos += 3 * (CARD_PADDING(window) + CARD_SIZE_X(window));

	for (int i = 0; i < 4; i++)
	{
		render_texture_as_image_resized(window, t_map->card_blank, x_pos, y_pos, CARD_SIZE(window));
		x_pos += CARD_PADDING(window) + CARD_SIZE_X(window);
	}
}

void render_stock_pile(window_t* window, texture_map_t* t_map, card_manager_t* card_man)
{
	int x_pos = (int)round(window->width  * 0.065); // 6.5% margin
	int y_pos = (int)round(window->height * 0.025); // 2.5% margin

	render_texture_as_image_resized(window, t_map->card_back, x_pos, y_pos, CARD_SIZE(window));
}

void render_talon_pile(window_t* window, texture_map_t* t_map, card_manager_t* card_man)
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

card_manager_t* create_and_randomize_card_manager()
{
	card_manager_t* card_man = calloc(1, sizeof(card_manager_t));

	// TODO: rewrite this and use dynamic array to random sort cards
	
	card_t cards_copy[52];
	memcpy(cards_copy, all_cards, 52 * sizeof(card_t));

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < (i + 1); j++)
		{
			card_t random_card;
			int random_num;
			do {
				random_num = (int)round(random_number() * 52);
				random_card = cards_copy[random_num];
			} while (random_card.k != 1);

			card_man->tableau[i][j] = random_card;
			cards_copy[random_num].k = 1;
			if (j == i)
				card_man->tableau[i][j].hidden = false;
		}
	}

}

void card_manager_destroy(card_manager_t* card_man)
{
	free(card_man);
}