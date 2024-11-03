#include <logic.h>
#include <cards.h>
#include <core.h>

const char cards_value[13] = {
    'A', '2', '3', '4', '5', 
    '6', '7', '8', '9', '1', // '1' == 10
    'J', 'Q', 'K'
};

/*
 * This file is going to implement
 * basic logic of Solitaire 
 */

int logic_get_card_value(char card_value)
{   
    for (int i = 0; i < 13; i++)
        if (cards_value[i] == card_value)
            return i;
    
    /* Unreachable code but incase we get here */
    printf("runtime error: this code should be unreachable. %s\n", __FILE__);
    assert(1 == 0);
}

bool logic_are_cards_different_colors(card_t cf, card_t cs)
{
    // true - black, false - red
    bool cf_color = (cf.id[0] == 'C' || cf.id[0] == 'S') ? true : false;
    bool cs_color = (cs.id[0] == 'C' || cs.id[0] == 'S') ? true : false;

    return ((cf_color == cs_color) == false);
}

bool logic_cards_values_are_decresing(card_t cf, card_t cs)
{
    /* Let's get the `cf` and `cs` REAL card value.
     * By REAL i mean that we count also cards without 
     * numeral notation like King, Queen etc. */
    int cf_real_value = logic_get_card_value(cf.id[1]);
    int cs_real_value = logic_get_card_value(cs.id[1]);

    if (cf_real_value == (cs_real_value + 1))
        return true;
    else
        return false;
}

bool logic_can_card_be_placed(card_t cf, card_t cs)
{
    /* First check are the cards different colors to obtain
     * this alternating pattern */
    if (logic_are_cards_different_colors(cf, cs) == false)
        return false;

    /* After that we check are the cards values decreasing 
     * so the card cf is one bigger in the value */
    if (logic_cards_values_are_decresing(cf, cs) == false)
        return false;

    return true;
}