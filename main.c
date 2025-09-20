/*
    main code for running the blackjack game
*/

#include "card.h"
#include "cardlist.h"
#include "game.h"
#include "utils.h"
#include <stdint.h>
#include <string.h>
#include <time.h>

int main(void) {
  printf("\033[2J\033[H"); // Cleans the terminal

  srand(time(NULL));

  struct Game *game = malloc(sizeof(Game));
  MY_ASSERT(game != NULL, "malloc failed");

  game_init(game);
  game_run(game);
  free_game(game);
  return 0;
}
