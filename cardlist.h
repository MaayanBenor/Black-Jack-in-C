#pragma once
#include "card.h"

typedef struct CardList CardList;

struct CardList
{
    Card *head;
    Card *tail;

    size_t len;
};

void init_cardlist(CardList *cardlist);
void clear_cardlist(CardList *cardlist);
void fill_deck(CardList *cardlist);
void card_draw(CardList *source, CardList *dest);
Card *card_remove_at(CardList *cardlist, size_t index);
void card_push(CardList *cardlist, Card *const card);
Card *card_pop(CardList *cardlist);
void print_cardlist(CardList const * const cardlist);
void draw_all(CardList *source, CardList *dest);
int hand_value(CardList *hand);


void test_cardlist();