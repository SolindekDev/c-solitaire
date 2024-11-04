#include <array.h>
#include <SDL2/SDL_events.h>
#include <cards.h>
#include <logic.h>
#include <random.h>
#include <render.h>
#include <texture.h>
#include <thirdparty.h>
#include <window.h>
#include <utils.h>

struct card_find_t {
	card_t* card;
	int row_index, col_index;
	bool tableau, foundation, stock, talon;
};

static bool card_dragging = false;
static struct card_find_t card_dragging_data;
static int card_dragging_x;
static int card_dragging_y;

static bool card_several_dragging = false;
static array_t* card_several_dragging_data = false;

void render_cards(window_t *window, texture_map_t *t_map,
                  card_manager_t *card_man) 
{
  /* In Solitaire we recognize 4 diffrent piles:
   *  1. Tableau - Seven piles that make up the main table.
   *  2. Foundation - Four piles on which a whole suit or sequence must be built
   * up.
   *  3. Stock (or Hand) - If the entire pack is not laid out in a tableau at
   * the beginning of a game, the remaining cards form the stock pile from which
   * additional cards are brought into play according to the rules.
   *  4. The Talon (or Waste) - Cards from the stock pile that have no place in
   * the tableau or on foundations
   */

  render_tableau_pile(window, t_map, card_man);
  render_foundation_pile(window, t_map, card_man);
  render_stock_pile(window, t_map, card_man);
  render_talon_pile(window, t_map, card_man);
}

void render_tableau_pile(window_t *window, texture_map_t *t_map,
                         card_manager_t *card_man) 
{
	int x_pos = (int)round(window->width * 0.065); // 6.5% margin

	for (int i = 0; i < 7; i++) 
	{
		int y_pos = (int)round(window->height * 0.05) +
					CARD_SIZE_Y(window); // 2.5% margin + card_size y + 2.5% margin

		for (int j = 0; j < 13; j++) 
		{
			card_t card = card_man->tableau[i][j];

			if (card.path == NULL)
				break;

			int x = x_pos;
			int y = y_pos;

			if (card_dragging == true && card_several_dragging == false)
			{
				x = card.i == card_dragging_data.card->i
							? card_dragging_x - (CARD_SIZE_X(window) / 2)
							: x_pos;
				y = card.i == card_dragging_data.card->i
							? card_dragging_y - (CARD_SIZE_Y(window) / 2)
							: y_pos;
			}

			if (card_several_dragging == true)
			{
				for (int k = 0; k < card_several_dragging_data->length; k++)
				{
					char* curr_card_id = ((card_t*)get_element_from_array(card_several_dragging_data, (unsigned long)k))->id;
					// printf("%s\n", curr_card_id);
					if (strcmp(curr_card_id, card.id) == 0)
					{
						x = card_dragging_x - (CARD_SIZE_X(window) / 2);
						y = card_dragging_y - (CARD_SIZE_Y(window) / 2) + (30 * k);
					}
				}
			}
			

			if (!card.hidden)
				render_texture_as_image_resized(window,
												t_map->cards[card.i]->card_texture,
												x, y, CARD_SIZE(window));
			else
				render_texture_as_image_resized(window, t_map->card_back, x, y,
												CARD_SIZE(window));
			y_pos += 30;
		}

		x_pos += CARD_PADDING(window) + CARD_SIZE_X(window);
	}
}

void render_foundation_pile(window_t *window, texture_map_t *t_map,
                            card_manager_t *card_man) 
{
  int x_pos = (int)round(window->width * 0.065);  // 6.5% margin
  int y_pos = (int)round(window->height * 0.025); // 2.5% margin

  x_pos += 3 * (CARD_PADDING(window) + CARD_SIZE_X(window));

  for (int i = 0; i < 4; i++) {
    render_texture_as_image_resized(window, t_map->card_blank, x_pos, y_pos,
                                    CARD_SIZE(window));
    x_pos += CARD_PADDING(window) + CARD_SIZE_X(window);
  }
}

void render_stock_pile(window_t *window, texture_map_t *t_map,
                       card_manager_t *card_man) 
{
  int x_pos = (int)round(window->width * 0.065);  // 6.5% margin
  int y_pos = (int)round(window->height * 0.025); // 2.5% margin

  render_texture_as_image_resized(window, t_map->card_back, x_pos, y_pos,
                                  CARD_SIZE(window));
}

void render_talon_pile(window_t *window, texture_map_t *t_map,
                       card_manager_t *card_man) 
{
	if (card_man->talon_size != 0)
	{
		int x_pos = (int)round(window->width * 0.065) + CARD_SIZE_X(window) + (CARD_PADDING(window) / 2); 
		int y_pos = (int)round(window->height * 0.025); 

		card_t card = card_man->talon[card_man->talon_size - 1];

		if (card_dragging)
			if (card_dragging_data.talon == true)
				if (card.i == card_dragging_data.card->i)
				{
					x_pos = card_dragging_x - CARD_SIZE_X(window) / 2;
					y_pos = card_dragging_y - CARD_SIZE_X(window) / 2;
				}

		render_texture_as_image_resized(window, t_map->cards[card.i]->card_texture, x_pos, y_pos,
										CARD_SIZE(window));
	}
}

card_texture_t *create_card_texture_from_card_t(window_t *window, card_t card) 
{
  card_texture_t *card_texture = calloc(1, sizeof(card_texture_t));
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

void load_all_cards_textures(window_t *window, texture_map_t *t_map) 
{
  /* This function basically goes through all the playing
   * cards defined in `all_cards` and load's them to the
   * `t_map->cards` array */
  printf("%p\n", t_map);
  t_map->cards = calloc(52, sizeof(card_texture_t *));

  for (int i = 0; i < 52; i++) 
	{
    card_t current_card = all_cards[i];

    card_texture_t *card_texture =
        create_card_texture_from_card_t(window, current_card);

    // TODO: add better handling of card loading error
    if (card_texture == NULL) 
		{
      texture_map_destroy(t_map);
      window_destroy(window);
      quit_thirdparty();
    }

    t_map->cards[i] = card_texture;
    printf("loaded card: id=%s, path=%s, texture=%p\n", card_texture->id,
           card_texture->path, card_texture->card_texture);
  }
}

card_manager_t *create_and_randomize_card_manager() 
{
  card_manager_t *card_man = calloc(1, sizeof(card_manager_t));
  array_t *card_copy = create_array(52 * sizeof(card_t *));

  card_man->stock_size = 24;
  card_man->talon_size = 0;

  // Copy all elements from `all_cards` to `card_copy`
  for (int i = 0; i < 52; i++) 
	{
    card_t *card = malloc(sizeof(card_t));
    memcpy(card, &all_cards[i], sizeof(card_t));

    append_element_to_array(card_copy, card);
  }

  unsigned long available_cards = card_copy->length;

  for (int i = 0; i < 7; i++) 
	{
    for (int j = 0; j < (i + 1); j++) 
		{
      int random_num = (int)round(random_number() * ((int)available_cards - 1));
      card_t *random_card =
          get_element_from_array(card_copy, (unsigned long)random_num);
      if (j == i)
        random_card->hidden = false;

      // Copy this card to the tableau and delete it from the
      // available cards array
      memcpy(&card_man->tableau[i][j], random_card, sizeof(card_t));
      delete_element_from_array(card_copy, (unsigned long)random_num);
      available_cards--;
    }
  }

  for (int k = 0; k < card_copy->length; k++)
  {
	card_t* card = get_element_from_array(card_copy, (unsigned long)k);
	memcpy(&card_man->stock[k], card, sizeof(card_t));
  }

  for (int l = 0; l < card_copy->length; l++)
    free(get_element_from_array(card_copy, (unsigned long)l));
  free(card_copy);

  return card_man;
}

void card_manager_destroy(card_manager_t *card_man) 
{ 
	free(card_man); 
}

int card_calculate_tableau_card_length(card_manager_t* card_man, int tableau_column)
{
	int n = 0; 

	while (card_man->tableau[tableau_column][n].path != NULL)
		n++;

	return n;
}

struct card_find_t card_find_out_by_mouse_position(card_manager_t *card_man,
                                            window_t *window, int mouse_x,
                                            int mouse_y) 
{
	// First of all find out where is the mouse heading more foundation, 
	// stock and pile or just the tableau

	int tableau_start = (int)round(window->height * 0.050) + CARD_SIZE_Y(window);
	int stock_start   = (int)round(window->height * 0.025);
	
	if (mouse_y > tableau_start)
	{
		// We are heading more to the tableau, now we are going to find out
		// the x location, so on which pile we are clicking from 1 to 7
		int x_pos_start = (int)round(window->width * 0.065);
		int x_pos_end   = window->width - (int)round(window->width * 0.065);

		if (mouse_x > x_pos_start && mouse_x < x_pos_end)
		{
			// Find out is the mouse even pointing at a card or between the paddings
			int absolute_position_x   = mouse_x - ((int)round(window->width * 0.065));
			float estimated_column_x  = (float)absolute_position_x / (CARD_PADDING(window) + CARD_SIZE_X(window));

			int   integer_part_x = (int)estimated_column_x;
			float decimal_part_x = estimated_column_x - integer_part_x;

			if (decimal_part_x >= 0.0 && decimal_part_x <= 0.7) 
			{
				if (integer_part_x >= 0 && integer_part_x <= 6) 
				{
					// Yes the mouse i pointing at a card lets now calculated it y index offset
					int card_start = mouse_y - tableau_start;
					int estimated_card_y = (int)(card_start / 30.0f);

					int column_cards_length = card_calculate_tableau_card_length(card_man, integer_part_x);

					if (estimated_card_y < column_cards_length)
						return (struct card_find_t) 
								{ .card = &card_man->tableau[integer_part_x][estimated_card_y],
								  .col_index = integer_part_x, .row_index = estimated_card_y,
								  .tableau = true };
					else if ((float)estimated_card_y < (float)(column_cards_length + 3))
						return (struct card_find_t) 
								{ .card = &card_man->tableau[integer_part_x][column_cards_length - 1],
								  .col_index = integer_part_x, .row_index = column_cards_length - 1,
								  .tableau = true };
					else
						return (struct card_find_t) { .card = NULL, .col_index = integer_part_x, .tableau = true };
				}
			} else
				return (struct card_find_t) { .card = NULL };
		}	
		else
			return (struct card_find_t) { .card = NULL };
	}
	if (card_man->talon_size != 0)
	{
		int talon_x_pos = (int)round(window->width * 0.065) + CARD_SIZE_X(window) + (CARD_PADDING(window) / 2); 
		int talon_y_pos = (int)round(window->height * 0.025); 

		if (check_box_collision(talon_x_pos, talon_y_pos, CARD_SIZE(window), mouse_x, mouse_y, 1, 1))
		{
			return (struct card_find_t) {
				.card = &card_man->talon[card_man->talon_size - 1], 
				.row_index = -1, .col_index = -1,
				.talon = true,
			};
		}
	}
	else 
	{
		// TODO: Foundation, stock and pile type shit
	}

	return (struct card_find_t) { .card = NULL };
}

void card_stock_clicked(window_t* window, card_manager_t* card_man)
{
	/* If we clicked the stock we need to the card from the top
	* to the talon pile */

	card_man->talon_size++;
	card_man->stock_size--;

	for (int i = 0; i < card_man->stock_size; i++)
		printf("- %d=%s\n", i, card_man->stock[i].path);

	// TODO: Add that when the stock size equals 0 it restarts
	memcpy(&card_man->talon[card_man->talon_size - 1], &card_man->stock[card_man->stock_size - 1], sizeof(card_t));
	memset(&card_man->stock[card_man->stock_size - 1], 0, sizeof(card_t));
	return;
}

void card_drag_event(card_manager_t *card_man, window_t *window,
                     SDL_Event event) 
{
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (card_dragging != true)
			return;

		int mouse_x = event.button.x;
		int mouse_y = event.button.y;

		struct card_find_t mouse_on_card = card_find_out_by_mouse_position(card_man, window, mouse_x, mouse_y);

		if (card_several_dragging == false)
		{
			// Prevent from some weird shit to happend
			if (mouse_on_card.col_index == card_dragging_data.col_index)
			{
				card_dragging = false;
				return;
			}

			if (mouse_on_card.tableau)
			{	
				int row_index = mouse_on_card.row_index;
				if (mouse_on_card.card == NULL)
					row_index = card_calculate_tableau_card_length(card_man, mouse_on_card.col_index) - 1;

				if (!logic_can_card_be_placed(
							card_man->tableau[mouse_on_card.col_index][row_index], 
							card_man->tableau[card_dragging_data.col_index][card_dragging_data.row_index]))
				{
					printf("This move is illegal to perform.\n");
					card_dragging = false;
					return;
				}

				memcpy(&card_man->tableau[mouse_on_card.col_index][row_index + 1],
							&card_man->tableau[card_dragging_data.col_index][card_dragging_data.row_index], sizeof(card_t));
				memset(&card_man->tableau[card_dragging_data.col_index][card_dragging_data.row_index], 0, sizeof(card_t));

				if ((card_dragging_data.row_index - 1) != -1)
					card_man->tableau[card_dragging_data.col_index][card_dragging_data.row_index - 1].hidden = false;
			}
			else
				printf("TODO: performing this action on different piles\n");
		}
		else
		{
			if (mouse_on_card.col_index == card_dragging_data.col_index)
			{
				card_dragging = false;
				card_several_dragging = false;
				return;
			}

			if (mouse_on_card.tableau && card_dragging_data.tableau)
			{	
				card_t* first_card = get_element_from_array(card_several_dragging_data, 0);
				int row_index = mouse_on_card.row_index;
				if (mouse_on_card.card == NULL)
					row_index = card_calculate_tableau_card_length(card_man, mouse_on_card.col_index) - 1;

				if (!logic_can_card_be_placed(card_man->tableau[mouse_on_card.col_index][row_index], *first_card))
				{
					printf("This move is illegal to perform.\n");
					card_dragging = false;
					card_several_dragging = false;
					return;
				}

				printf("This move can be performed.\n");

				for (int i = 0; i < card_several_dragging_data->length; i++)
				{
					memcpy(&card_man->tableau[mouse_on_card.col_index][row_index + i + 1], 
							get_element_from_array(card_several_dragging_data, (unsigned long)i), sizeof(card_t));
					memset(&card_man->tableau[card_dragging_data.col_index][card_dragging_data.row_index + i], 0, sizeof(card_t));
				}

				if ((card_dragging_data.row_index - 1) != -1)
					card_man->tableau[card_dragging_data.col_index][card_dragging_data.row_index - 1].hidden = false;
			}
			else
				printf("TODO: performing this action on different piles\n");
		}

		card_dragging = false;
		card_several_dragging = false;
	}
	else if (event.type == SDL_MOUSEMOTION)
	{
		if (card_dragging == true)
		{
			int mouse_x = event.button.x;
			int mouse_y = event.button.y;

			card_dragging_x = mouse_x;
			card_dragging_y = mouse_y;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		int mouse_x = event.button.x;
		int mouse_y = event.button.y;

		int stock_x_pos = (int)round(window->width  * 0.065);  
		int stock_y_pos = (int)round(window->height * 0.025);  

		if (check_box_collision(stock_x_pos, stock_y_pos, CARD_SIZE(window), mouse_x, mouse_y, 1, 1))
			card_stock_clicked(window, card_man);
		else
		{
			struct card_find_t mouse_on_card = card_find_out_by_mouse_position(card_man, window, mouse_x, mouse_y);

			if (mouse_on_card.talon == true)
			{
				if (mouse_on_card.card != NULL)
				{
					card_dragging = true;
					card_dragging_data = mouse_on_card;
					card_dragging_x = mouse_x;
					card_dragging_y = mouse_y;
				}
			} 
			else if (mouse_on_card.tableau == true)
			{
				if (mouse_on_card.card != NULL)
				{
					if (mouse_on_card.card->hidden == true)
						return;

					int all_cards_in_col = card_calculate_tableau_card_length(card_man, mouse_on_card.col_index);

					// If it's the last card in the column
					if (all_cards_in_col - 1 == mouse_on_card.row_index)
					{
						printf("only one drag\n");
						card_dragging = true;
						card_dragging_data = mouse_on_card;
						card_dragging_x = mouse_x;
						card_dragging_y = mouse_y;
					}
					else
					{
						printf("multiply drag\n");
						card_dragging = true;
						card_several_dragging = true;
						card_several_dragging_data = create_array(sizeof(card_t*));
						card_dragging_data = mouse_on_card;
						card_dragging_x = mouse_x;
						card_dragging_y = mouse_y;

						for (int i = mouse_on_card.row_index; i < all_cards_in_col; i++)
						{
							append_element_to_array(card_several_dragging_data, 
								&card_man->tableau[mouse_on_card.col_index][i]);
						}
					}
				}
			}
		}
	}
}