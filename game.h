#include "cardlist.h"
#include <stdbool.h>

#define MIN_BET 10 // minumum betting amount is 10

typedef struct Game Game;
struct Game
{
    CardList *deck;
    CardList *player_hand;
    CardList *dealer_hand;

    size_t pot, cash;
};
//utility
void game_init(Game *game);
void print_game_state(Game const *const game);
void free_game(Game *game);
void test_game();
void print_pot_cash(Game *game);
bool is_bet_valid(size_t bet, Game *game);
void print_hands(Game *game, bool display_full_dealer_hand);
void print_hands_end_game(Game *game);
void player_win(Game *game, bool is_black_jack);
void player_lose(Game *game, bool is_bust);
void tie(Game *game);
void game_run(Game *game);

//game phases
void bet_phase(Game *game);
void initial_deal(Game *game);
bool is_black_jack(Game *game);
int hit_or_stand(Game *game);
void dealer_draw(Game *game);

void reset_cards(Game *game);
bool continue_playing(Game *game);

