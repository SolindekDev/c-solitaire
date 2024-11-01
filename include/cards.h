#ifndef CARDS_H
#define CARDS_H

#include <window.h>
#include <texture.h>

typedef struct __card_t {
    char id[4]; /* For example: "D2" for 2 of Diamonds, null-terminated */
    char* path;
} card_t;

#define CARD_BACK_PATH "./assets/cards/card_back.png"
#define CARD_SIZE 164, 233

static card_t all_cards[] = {
    {"D2", "./assets/cards/white/D2.png"},   
    {"D3", "./assets/cards/white/D3.png"},   
    {"D4", "./assets/cards/white/D4.png"},
    {"D5", "./assets/cards/white/D5.png"},   
    {"D6", "./assets/cards/white/D6.png"},   
    {"D7", "./assets/cards/white/D7.png"},
    {"D8", "./assets/cards/white/D8.png"},   
    {"D9", "./assets/cards/white/D9.png"},   
    {"D10","./assets/cards/white/D10.png"},
    {"DJ", "./assets/cards/white/DJ.png"},   
    {"DQ", "./assets/cards/white/DQ.png"},   
    {"DK", "./assets/cards/white/DK.png"},
    {"DA", "./assets/cards/white/DA.png"},   
    {"H2", "./assets/cards/white/H2.png"},   
    {"H3", "./assets/cards/white/H3.png"},
    {"H4", "./assets/cards/white/H4.png"},   
    {"H5", "./assets/cards/white/H5.png"},   
    {"H6", "./assets/cards/white/H6.png"},
    {"H7", "./assets/cards/white/H7.png"},   
    {"H8", "./assets/cards/white/H8.png"},   
    {"H9", "./assets/cards/white/H9.png"},
    {"H10","./assets/cards/white/H10.png"}, 
    {"HJ", "./assets/cards/white/HJ.png"},   
    {"HQ", "./assets/cards/white/HQ.png"},
    {"HK", "./assets/cards/white/HK.png"},   
    {"HA", "./assets/cards/white/HA.png"},   
    {"C2", "./assets/cards/white/C2.png"},
    {"C3", "./assets/cards/white/C3.png"},   
    {"C4", "./assets/cards/white/C4.png"},   
    {"C5", "./assets/cards/white/C5.png"},
    {"C6", "./assets/cards/white/C6.png"},   
    {"C7", "./assets/cards/white/C7.png"},   
    {"C8", "./assets/cards/white/C8.png"},
    {"C9", "./assets/cards/white/C9.png"},   
    {"C10","./assets/cards/white/C10.png"},
    {"CJ", "./assets/cards/white/CJ.png"},
    {"CQ", "./assets/cards/white/CQ.png"},   
    {"CK", "./assets/cards/white/CK.png"},   
    {"CA", "./assets/cards/white/CA.png"},
    {"S2", "./assets/cards/white/S2.png"},   
    {"S3", "./assets/cards/white/S3.png"},   
    {"S4", "./assets/cards/white/S4.png"},
    {"S5", "./assets/cards/white/S5.png"},   
    {"S6", "./assets/cards/white/S6.png"},   
    {"S7", "./assets/cards/white/S7.png"},
    {"S8", "./assets/cards/white/S8.png"},   
    {"S9", "./assets/cards/white/S9.png"},   
    {"S10","./assets/cards/white/S10.png"},
    {"SJ", "./assets/cards/white/SJ.png"},   
    {"SQ", "./assets/cards/white/SQ.png"},   
    {"SK", "./assets/cards/white/SK.png"},
    {"SA", "./assets/cards/white/SA.png"},
};

typedef struct __texture_t texture_t;
typedef struct __texture_map_t texture_map_t;

typedef struct __card_texture_t {
    char id[4];
    const char* path;
    texture_t* card_texture;
} card_texture_t;

void render_cards(window_t* window, texture_map_t* t_map);

void render_tableau_pile(window_t* window, texture_map_t* t_map);
void render_foundation_pile(window_t* window, texture_map_t* t_map);
void render_stock_pile(window_t* window, texture_map_t* t_map);
void render_talon_pile(window_t* window, texture_map_t* t_map);

void load_all_cards_textures(window_t* window, texture_map_t* t_map);

#endif /* CARDS_H */