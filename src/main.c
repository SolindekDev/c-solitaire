#include "cards.h"
#include "random.h"
#include <core.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <window.h>
#include <thirdparty.h>
#include <texture.h>
#include <errors.h>
#include <render.h>

/* Default options for creating a window */
#define DEFAULT_OPT "CSolitaire", 1450, 890

void loop_logic(window_t* w)
{
	/* 
	 * This function defines everything what happens
	 * each frame. 
	 */	

	window_start_fps_measuring(w);

	card_manager_t* card_man = create_and_randomize_card_manager();
	texture_map_t* t_map = create_texture_map(w);
	texture_t* bg = create_texture(w, "./assets/bg.png");

	while (window_should_exit(w))
	{
		window_handle_events(w, card_man);
		window_clear_renderer(w);

		/* Render */
		render_texture_as_background(w, bg);
		render_cards(w, t_map, card_man);

		window_present(w);
		window_measure_fps(w);
	}

	card_manager_destroy(card_man);
	texture_map_destroy(t_map);
	texture_destroy(bg);
	window_destroy(w);
}

int main(int argc, char** argv) 
{
  /* First of all initialize SDL2 and SDL_ttf */
  unsigned char _it;
  if ((_it = initialize_thirdparty()) != EXIT_SUCCESS)
    return _it;

  window_t* w;
  if ((w = create_window(DEFAULT_OPT)) == NULL)
		EXIT_WITH_ERROR_SDL(err_CREATE_WINDOW);

	init_random_numbers();
	loop_logic(w);
  return quit_thirdparty();
}