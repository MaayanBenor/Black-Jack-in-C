
#include "card.h"
#include "utils.h"
#include <string.h>

const char *HIGH_NIBBLE_RANK_LOOKUP[16] =
    {
        //"invalid" values are fillers if the
        // given number is not a valid card
        /*0000*/ "invalid",
        /*0001*/ "Ace",
        /*0010*/ "2",
        /*0011*/ "3",
        /*0100*/ "4",
        /*0101*/ "5",
        /*0110*/ "6",
        /*0111*/ "7",
        /*1000*/ "8",
        /*1001*/ "9",
        /*1010*/ "10",
        /*1011*/ "Jack",
        /*1100*/ "Queen",
        /*1101*/ "King",
        /*1110*/ "invalid",
        /*1111*/ "invalid",
};

const char *card_suit(Card const *const card) {
  // made with a switch case insted of a lookup table for
  // safety reasons. this way there is no need for "invalid"
  // slots in the array and storage isn't wasted on them.
  // so here I lose runtime speed for more storage and espacially
  // more code safety. this way even if another programmer tries to
  //  send an invalid card here somehow, it will fail.
  MY_ASSERT(card != NULL, "card cannot be NULL");
  u8 low_nibble = card->data & 0x0F;
  switch (low_nibble) {
  case 1:
    return "Hearts";
  case 2:
    return "Clubs";
  case 4:
    return "Diamonds";
  case 8:
    return "Spades";
  default:
    MY_ASSERT(false, "invalid card suit");
    return NULL;
  }
}

const char *card_rank(Card const *const card) {
  MY_ASSERT(card != NULL, "card cannot be NULL");

  u8 high_nibble = (card->data >> 4) & 0x0F;
  return HIGH_NIBBLE_RANK_LOOKUP[high_nibble];
}

Card *card_new(u8 const rank, u8 const suit) {

  // check for invalid card values
  MY_ASSERT(rank >= 1 && rank <= 13, "invalid card rank");
  MY_ASSERT(suit == 1 || suit == 2 || suit == 4 || suit == 8, "invalid card suit");

  Card *card = malloc(sizeof(Card));
  MY_ASSERT(card != NULL, "malloc failed");

  // combine rank and suit to one variable
  u8 data = (rank << 4) | suit;

  card->data = data;
  card->next = NULL;
  return card;
}

void print_card(Card const *const card) {
  MY_ASSERT(card != NULL, "card cannot be NULL");

  const char *c_suit = card_suit(card);

  if (strcmp(c_suit, "Hearts") == 0 || strcmp(c_suit, "Diamonds") == 0) {
    printf(RED);
  }
  printf("%s of %s", card_rank(card), c_suit);
  printf(RST);
}

void print_card_bits(Card const *const card) // for testing purposes
{
  MY_ASSERT(card != NULL, "card cannot be NULL");

  u8 data = card->data;
  for (size_t i = 0; i < sizeof(u8) * 8; i++) {
    data & 0x80 ? putchar('1') : putchar('0');
    data <<= 1;
    if (i == 3) {
      printf(" "); // seperates to nibbles
    }
  }
}

void card_test(u8 const rank, u8 const suit) // for testing purposes
{
  Card *card = card_new(rank, suit);
  print_card(card);
  printf(" ");
  print_card_bits(card);
  puts("");

  free(card);
  card = NULL;
}

int card_value(Card const *const card) {
  u8 high_nibble_value = (card->data >> 4) & 0x0F;

  if (high_nibble_value > 9) {
    high_nibble_value = 10;
  }

  return high_nibble_value;
}
