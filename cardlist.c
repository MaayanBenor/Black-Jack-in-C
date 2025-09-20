#include "cardlist.h"
#include "card.h"
#include "utils.h"

enum {
  // anonymous enum because I only need the compile time constants
  // and will not need to use the enum itself.
  NUM_RANKS = 13,
  NUM_SUITS = 4
};

void init_cardlist(CardList *cardlist) {
  cardlist->head = NULL;
  cardlist->tail = NULL;
  cardlist->len = 0;
}

void fill_deck(CardList *cardlist) {
  MY_ASSERT(cardlist != NULL, "cardlist cannot be NULL");
  // assumes list is empty
  for (int i = 0; i < NUM_RANKS; i++) {
    for (int j = 0; j < NUM_SUITS; j++) { // i + 1 = actual card value 1-13
      card_push(cardlist, card_new(i + 1, 1 << j));
    }
  }
}

void clear_cardlist(CardList *cardlist) {
  Card *card;
  while (cardlist->head != NULL) {
    // advance through the list
    card = cardlist->head;
    cardlist->head = card->next;

    // make it point to NULL
    card->next = NULL;

    // free the malloced node
    free(card);
  }
  cardlist->len = 0;
}

void card_draw(CardList *source, CardList *dest) {
  MY_ASSERT(dest != NULL, "can't operate on NULL dest cardlist");
  MY_ASSERT(source != NULL, "can't operate on NULL source cardlist");
  card_push(dest, card_remove_at(source, rand() % source->len));
}

Card *card_remove_at(CardList *cardlist, size_t index) {
  MY_ASSERT(cardlist != NULL, "cardlist cannot be NULL");
  MY_ASSERT(index <= cardlist->len, "invalid index");

  Card *curr = cardlist->head;
  Card *prev = NULL;
  while (index--) {
    prev = curr;
    curr = curr->next;
    // gets curr to the desired index
  }

  if (prev == NULL) { // curr == head

    if (cardlist->head == cardlist->tail) { // cardlist->len == 1

      cardlist->head = NULL;
      cardlist->tail = NULL;
    } else { // ther}e are more nodes after curr

      cardlist->head = curr->next;
    }
  } else if (cardlist->tail == curr) // curr == tail
  {
    cardlist->tail = prev;
    cardlist->tail->next = NULL;
  } else // card isn't tail or head
  {
    prev->next = curr->next;
  }

  cardlist->len--;
  curr->next = NULL;
  return curr;
}

void card_push(CardList *cardlist, Card *card) {
  MY_ASSERT(cardlist != NULL, "cardlist cannot be NULL");
  if (cardlist->head != NULL) // first check if isn't NULL because most cases it will not be
  {                           //(filling a deck, all card draws besides the first)
    card->next = cardlist->head;
    cardlist->head = card;
  } else {
    cardlist->head = card;
    cardlist->tail = card;
    // card->next already points to NULL
  }

  cardlist->len++; // needs to happen in both cases
}

Card *card_pop(CardList *cardlist) {
  MY_ASSERT(cardlist != NULL, "cardlist cannot be NULL"); // TODO: ask shmuel if this is neccasery

  Card *head = cardlist->head; // cardlist is initialized if cardlist != NULl
                               // so head must exist, even if it's NULL
  MY_ASSERT(head != NULL, "cardlist->head cannot be NULL");

  cardlist->head = head->next;
  cardlist->len--;

  if (head == NULL) // list is empty
  {
    cardlist->tail = NULL;
  }

  return head;
}

void print_cardlist(CardList const *const cardlist) {
  MY_ASSERT(cardlist != NULL, "cardlist cannot be NULL");
  Card *card = cardlist->head;
  for (size_t i = 0; i < cardlist->len; i++) {
    print_card(card);
    if (i + 1 != cardlist->len) // checks if it isn't the last card
    {                           // if isn't, prints ', ' to seperate from the next card
      printf(", ");
    }
    card = card->next;

    // for printing the whole deck in a more orginized way:
    // if ((i + 1) % 4 == 0 && i != 0)
    // {
    //     puts("");
    // }
  }
}

void draw_all(CardList *source, CardList *dest) {
  MY_ASSERT(dest != NULL, "can't operate on NULL dest cardlist");
  MY_ASSERT(source != NULL, "can't operate on NULL source cardlist");

  while (source->head != NULL) {
    card_push(dest, card_pop((source)));
  }
}

int hand_value(CardList *hand) {
  MY_ASSERT(hand != NULL, "hand cardlist cannot be NULL");
  
  int sum = 0, value;
  Card *curr = hand->head;
  bool has_ace = false;
  while (curr != NULL) {
    value = card_value(curr);
    sum += value;
    curr = curr->next;
    if (value == 1) { has_ace = true; }
  }

  if (has_ace) {
    sum += 10; // adding the remaining 10 of the ace.
    return (sum > 21) ? (sum - 10) : sum;
  } else {
    return sum;
  }
  // printf("hand sum: %d", (sum > 21) ? (sum - 10) : sum);//for testing
  // purposes
}

void test_cardlist() {
  CardList *cardlist = malloc(sizeof(CardList));
  MY_ASSERT(cardlist != NULL, "malloc failed");

  init_cardlist(cardlist);
  fill_deck(cardlist);
  print_cardlist(cardlist);

  clear_cardlist(cardlist);
  free(cardlist);
  cardlist = NULL;
}
