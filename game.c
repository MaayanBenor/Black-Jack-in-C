#include <string.h>

#include "cardlist.h"
#include "game.h"
#include "utils.h"

#define WIN_MULTIPLIER 2
#define BL_WIN_MULTIPLIER 2.5

void game_init(Game *game) {
  // assigning memory
  game->player_hand = malloc(sizeof(CardList));
  MY_ASSERT(game->player_hand != NULL, "malloc failed");

  game->dealer_hand = malloc(sizeof(CardList));
  MY_ASSERT(game->dealer_hand != NULL, "malloc failed");

  game->deck = malloc(sizeof(CardList));
  MY_ASSERT(game->deck != NULL, "malloc failed");

  // initializing all cardlists in the game to NULL
  init_cardlist(game->player_hand);
  init_cardlist(game->dealer_hand);
  init_cardlist(game->deck);

  fill_deck(game->deck);

  game->cash = 1000;
  game->pot = 0;
}

void print_game_state(Game const *const game) {
  MY_ASSERT(game != NULL, "game cannot be NULL");
  printf("Game State:\n");
  printf("Player hand: ");
  print_cardlist(game->player_hand);
  puts("");
  printf("Dealer hand: ");
  print_cardlist(game->dealer_hand);
  puts("");
  printf("Numbers of cards in the deck: %zu\n", game->deck->len);

  printf("pot: %zu, total cash: %zu", game->pot, game->cash);
}

void free_game(Game *game) {
  MY_ASSERT(game != NULL, "game cannot be NULL");

  clear_cardlist(game->dealer_hand);
  clear_cardlist(game->player_hand);
  clear_cardlist(game->deck);
  game = NULL;
  free(game);
}

void test_game() {
  struct Game *game = malloc(sizeof(Game));
  MY_ASSERT(game != NULL, "malloc failed");

  game_init(game);
  print_game_state(game);
  free_game(game);
}

void print_pot_cash(Game *game) {
  MY_ASSERT(game != NULL, "game cannot be NULL");

  printf("pot: " GREEN "%zu" RST ", total cash: " GREEN "%zu" RST "\n", game->pot, game->cash);
}

bool is_bet_valid(size_t bet, Game *game) {

  // Not switch case because these are runtime conditions
  MY_ASSERT(game != NULL, "game cannot be NULL");

  if (bet % 10 != 0) {
    printf("Bets must be made in multiples of 10.\n");
    return false;
  } else if (bet > game->cash) {
    printf("I am sorry, but you do not have enough cash for this bet.\n");
    return false;
  } else if (game->pot > 0) // if pot > 0 there was a tie last round, so bet can be 0
  {
    return true;
  } else if (bet < MIN_BET) // bet can't be zero so if it is now return 1 to indicate failure
  {
    printf("The minimum betting amount is: %d.\n", MIN_BET);
    return false;
  }
  return true;
}

void print_hands(Game *game, bool display_full_dealer_hand) {
  MY_ASSERT(game != NULL, "game cannot be NULL");

  if (display_full_dealer_hand) {
    puts("");
    printf("dealer: ");
    print_cardlist(game->dealer_hand);
    puts("");

    printf("player: ");
    print_cardlist(game->player_hand);
    puts("\n");
  }

  else {
    puts("");
    printf("dealer: ");
    print_card(game->dealer_hand->head);
    puts(", ????????????"); //'?' amount == average of all card characters

    printf("player: ");
    print_cardlist(game->player_hand);
    puts("\n");
  }
}

void print_hands_end_game(Game *game) {
  puts("");
  printf("***** Hands at the end of the game *****\n\n");
  print_hands(game, true);
  puts("\n");
}

bool is_black_jack(Game *game) {
  MY_ASSERT(game != NULL, "game cannot be NULL");

  if (hand_value(game->player_hand) == 21) {
    if (hand_value(game->dealer_hand) == 21) {
      // in the guidlines for coding the game it doesn't say to check the dealer's hand
      // for a blackjack if the player has a black jack.
      // black jack rules say that if both dealer and player have 21 on the first hand
      // then it's a tie.
      // I sent an email with this question but with no answer so I coded it with
      // the rules of the game.

      tie(game);
    }

    else {
      player_win(game, true);
      return true;
    }
  }
  return false;
}

void player_win(Game *game, bool is_black_jack) {
  MY_ASSERT(game != NULL, "game cannot be NULL");

  int pot = game->pot;
  int prize = is_black_jack ? (pot * BL_WIN_MULTIPLIER)
                            : (pot * WIN_MULTIPLIER);

  print_hands_end_game(game);

  if (is_black_jack) {
    printf(GREEN "BLACK JACK!\n"); // RST happens in the next line
  }

  printf(GREEN "YOU WIN!\n" RST "Prize: %d\n", prize);

  // avoids wraparound if cash + prize > SIZE_MAX
  if ((SIZE_MAX - prize) < game->cash) {
    game->cash = SIZE_MAX;
  }

  else {
    game->cash += prize;
  }
  game->pot = 0;
}

void player_lose(Game *game, bool is_bust) {
  MY_ASSERT(game != NULL, "game cannot be NULL");

  print_hands_end_game(game);

  if (is_bust) {
    printf(RED "***** BUST *****\n" RST);
  }

  printf("You lose this round\n");
  game->pot = 0;
}

void tie(Game *game) {
  MY_ASSERT(game != NULL, "game cannot be NULL");

  print_hands_end_game(game);

  printf(YELLOW "***** Tie *****\n" RST
                "Money in the pot is retained for the next round, you may bet 0\n");
}

void game_run(Game *game) {
  while (1) // exiting the loop happens when the program is exited (no more money or user chooses "no")
  {
    bool need_dealer_draw = true;

    bet_phase(game);
    initial_deal(game); // deals 2 cards to player and dealer

    if (is_black_jack(game)) {
      // Player got Blackjack — instant win
      need_dealer_draw = false;
    }

    else if (hit_or_stand(game)) {
      // Player busted — instant loss
      need_dealer_draw = false;
    }

    if (need_dealer_draw) {
      dealer_draw(game);
    }

    reset_cards(game); // resets hands and deck
    if (!continue_playing(game)) {
      break;
    }
  }
}

// game phases
void bet_phase(Game *game) {
  MY_ASSERT(game != NULL, "game cannot be NULL");

  // storing the variables so they wouldn't need to be called from the struct each time. wastes storage for runtime.
  size_t pot = game->pot, cash = game->cash, bet = 0;

  do {
    print_pot_cash(game);

    printf("How much would you like to bet?: ");

    bet = get_user_input_size_t();
  } while (!is_bet_valid(bet, game));

  // updating game with correct values
  cash -= bet;
  pot += bet;
  game->cash = cash;
  game->pot = pot;
}

void initial_deal(Game *game) {
  MY_ASSERT(game != NULL, "game cannot be NULL");

  // draw 2 to dealer
  card_draw(game->deck, game->dealer_hand);
  card_draw(game->deck, game->dealer_hand);
  // draw 2 to player
  card_draw(game->deck, game->player_hand);
  card_draw(game->deck, game->player_hand);
}

int hit_or_stand(Game *game) {
  // returns '1' on player bust and '0' when player doesn't bust
  MY_ASSERT(game != NULL, "game cannot be NULL");

  // made into variables here so we wouldn't call on game-> every time.
  CardList *pdeck = game->deck;
  CardList *pplayer_hand = game->player_hand;
  char user_input[12]; // longest response is stand\0 which is 6 bytes

  while (1) {
    print_hands(game, false);
    printf("hit or stand?\n");
    scanf("%10s", user_input);
    clear_buffer();

    if (strcmp(user_input, "stand") == 0) {
      return 0;
    } else if (strcmp(user_input, "hit") == 0) {
      card_draw(pdeck, pplayer_hand);

      if ((hand_value(pplayer_hand)) > 21) {
        player_lose(game, true);
        return 1;
      }
      continue;
    }
    printf("I don't understand, type either 'hit' or 'stand'\n");
  }
  return 0;
}

void dealer_draw(Game *game) {
  MY_ASSERT(game != NULL, "game cannot be NULL");

  CardList *d_hand = game->dealer_hand;
  int player_hand_value = hand_value(game->player_hand);
  int dealer_hand_value;

  while ((dealer_hand_value = hand_value(d_hand)) < 17) // dealer is not allowed to draw if hand_value >=17
  {

    if (dealer_hand_value > player_hand_value) {
      player_lose(game, false);
      return;
    }

    card_draw(game->deck, d_hand);
  }

  if (dealer_hand_value > 21) {
    printf(YELLOW "***** Dealer BUST! *****\n" RST);
    player_win(game, false);
  } else if (dealer_hand_value > player_hand_value) {
    player_lose(game, false);
  } else if (player_hand_value > dealer_hand_value) // (dealer_hand_value == player_hand_value)
  {
    player_win(game, false);
  } else {
    tie(game);
  }
}

void reset_cards(Game *game) {
  MY_ASSERT(game != NULL, "game cannot be NULL");

  draw_all(game->dealer_hand, game->deck);
  draw_all(game->player_hand, game->deck);
}

bool continue_playing(Game *game) {
  MY_ASSERT(game != NULL, "game cannot be NULL");

  if (game->cash < 10 && game->pot == 0) {
    printf("You've spent it all! Please come again ;)\nGame over...\n");
    return false;
  }

  char user_input[12];
  while (1) {

    printf("Would you like to play again?\n"
           "yes/no\n");
    scanf("%10s", user_input);
    clear_buffer();

    if (strcmp(user_input, "no") == 0) {
      printf("Thank you for playing!\n");
      return false;
    }

    else if (strcmp(user_input, "yes") == 0) {
      break;
    }

    else {
      printf("I don't understand, type either 'yes' or 'no'\n");
    }
  }
  printf("\033[2J\033[H"); // Cleans the terminal
  return true;
}
