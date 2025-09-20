#pragma once
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef struct Card Card;

struct Card
{
    u8 data;
    Card *next;
};

Card *card_new(u8 const rank, u8 const suit);
const char *card_suit(Card const *const card);
const char *card_rank(Card const *const card);
void print_card(Card const *const card);
void print_card_bits(Card const *const card);
void card_test(u8 const rank, u8 const suit);
int card_value(Card const *const card);