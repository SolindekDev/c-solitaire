#ifndef CARDS_H
#define CARDS_H

#include <window.h>
#include <texture.h>

typedef struct __card_t {
    char id[4]; /* For example: "D2" for 2 of Diamonds, null-terminated */
    char* path;
    bool hidden;
    unsigned char k;
    unsigned char i;
} card_t;

#define CARD_BACK_PATH  "./assets/cards/card_back.png"
#define CARD_BLANK_PATH "./assets/cards/card_blank.png"
#define CARD_RATIO_SIZE_X 0.09034482758 // 131
#define CARD_RATIO_SIZE_Y 1.41984732820 // 186

#define CARD_SIZE(w) (int)(w->width * CARD_RATIO_SIZE_X), (int)((w->width * CARD_RATIO_SIZE_X) * CARD_RATIO_SIZE_Y)
#define CARD_SIZE_Y(w) (int)((w->width * CARD_RATIO_SIZE_X) * CARD_RATIO_SIZE_Y)
#define CARD_SIZE_X(w) (int)(w->width * CARD_RATIO_SIZE_X)

// #define CARD_PADDING(w) (((window->width - (2 * (window->width * 0.05))) / 7) - (w->width * CARD_RATIO_SIZE_X))
/* 
 * (((x - (2*(x*0.06))) / 7)-(x * y) = 9/70x-x * CARD_RATIO_SIZE_X 
 */
#define CARD_PADDING(w) (int)((0.12857142857 * w->width) - (w->width * CARD_RATIO_SIZE_X))

static card_t all_cards[] = {
	{"D2", "./assets/cards/white/2D.png", true, 0, 0},
	{"D3", "./assets/cards/white/3D.png", true, 0, 1},
	{"D4", "./assets/cards/white/4D.png", true, 0, 2},
	{"D5", "./assets/cards/white/5D.png", true, 0, 3},
	{"D6", "./assets/cards/white/6D.png", true, 0, 4},
	{"D7", "./assets/cards/white/7D.png", true, 0, 5},
	{"D8", "./assets/cards/white/8D.png", true, 0, 6},
	{"D9", "./assets/cards/white/9D.png", true, 0, 7},
	{"D10", "./assets/cards/white/10D.png", true, 0, 8},
	{"DJ", "./assets/cards/white/JD.png", true, 0, 9},
	{"DQ", "./assets/cards/white/QD.png", true, 0, 10},
	{"DK", "./assets/cards/white/KD.png", true, 0, 11},
	{"DA", "./assets/cards/white/AD.png", true, 0, 12},
	{"H2", "./assets/cards/white/2H.png", true, 0, 13},
	{"H3", "./assets/cards/white/3H.png", true, 0, 14},
	{"H4", "./assets/cards/white/4H.png", true, 0, 15},
	{"H5", "./assets/cards/white/5H.png", true, 0, 16},
	{"H6", "./assets/cards/white/6H.png", true, 0, 17},
	{"H7", "./assets/cards/white/7H.png", true, 0, 18},
	{"H8", "./assets/cards/white/8H.png", true, 0, 19},
	{"H9", "./assets/cards/white/9H.png", true, 0, 20},
	{"H10", "./assets/cards/white/10H.png", true, 0, 21},
	{"HJ", "./assets/cards/white/JH.png", true, 0, 22},
	{"HQ", "./assets/cards/white/QH.png", true, 0, 23},
	{"HK", "./assets/cards/white/KH.png", true, 0, 24},
	{"HA", "./assets/cards/white/AH.png", true, 0, 25},
	{"C2", "./assets/cards/white/2C.png", true, 0, 26},
	{"C3", "./assets/cards/white/3C.png", true, 0, 27},
	{"C4", "./assets/cards/white/4C.png", true, 0, 28},
	{"C5", "./assets/cards/white/5C.png", true, 0, 29},
	{"C6", "./assets/cards/white/6C.png", true, 0, 30},
	{"C7", "./assets/cards/white/7C.png", true, 0, 31},
	{"C8", "./assets/cards/white/8C.png", true, 0, 32},
	{"C9", "./assets/cards/white/9C.png", true, 0, 33},
	{"C10", "./assets/cards/white/10C.png", true, 0, 34},
	{"CJ", "./assets/cards/white/JC.png", true, 0, 35},
	{"CQ", "./assets/cards/white/QC.png", true, 0, 36},
	{"CK", "./assets/cards/white/KC.png", true, 0, 37},
	{"CA", "./assets/cards/white/AC.png", true, 0, 38},
	{"S2", "./assets/cards/white/2S.png", true, 0, 39},
	{"S3", "./assets/cards/white/3S.png", true, 0, 40},
	{"S4", "./assets/cards/white/4S.png", true, 0, 41},
	{"S5", "./assets/cards/white/5S.png", true, 0, 42},
	{"S6", "./assets/cards/white/6S.png", true, 0, 43},
	{"S7", "./assets/cards/white/7S.png", true, 0, 44},
	{"S8", "./assets/cards/white/8S.png", true, 0, 45},
	{"S9", "./assets/cards/white/9S.png", true, 0, 46},
	{"S10", "./assets/cards/white/10S.png", true, 0, 47},
	{"SJ", "./assets/cards/white/JS.png", true, 0, 48},
	{"SQ", "./assets/cards/white/QS.png", true, 0, 49},
	{"SK", "./assets/cards/white/KS.png", true, 0, 50},
	{"SA", "./assets/cards/white/AS.png", true, 0, 51},
};

typedef struct __texture_t texture_t;
typedef struct __texture_map_t texture_map_t;

typedef struct __card_texture_t {
    char id[4];
    const char* path;
    texture_t* card_texture;
} card_texture_t;
 
typedef struct __card_manager_t {
    card_t tableau[7][13];
    card_t stock[28];
} card_manager_t;

void render_cards(window_t* window, texture_map_t* t_map, card_manager_t* card_man);

void render_tableau_pile(window_t* window, texture_map_t* t_map, card_manager_t* card_man);
void render_foundation_pile(window_t* window, texture_map_t* t_map, card_manager_t* card_man);
void render_stock_pile(window_t* window, texture_map_t* t_map, card_manager_t* card_man);
void render_talon_pile(window_t* window, texture_map_t* t_map, card_manager_t* card_man);

void load_all_cards_textures(window_t* window, texture_map_t* t_map);

card_manager_t* create_and_randomize_card_manager();
void card_manager_destroy(card_manager_t* card_man);

#endif /* CARDS_H */