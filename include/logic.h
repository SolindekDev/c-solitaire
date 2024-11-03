#ifndef __LOGIC_H
#define __LOGIC_H

#include <cards.h>
#include <core.h>

bool logic_are_cards_different_colors(card_t cf, card_t cs);
bool logic_can_card_be_placed(card_t cf, card_t cs);

#endif /* __LOGIC_H */