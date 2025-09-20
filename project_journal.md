# Project Journal!

## Extra goals:
make runable versions of the finished game for windows and linux.

Add: 
1) easter eggs.

2) bots with different play styls.

3) a way to save the progression. 

4) minimum display size





### 05/06

I added TODO's today and I need to actively choose wether I want speed, storage or vonorability for my project.

If storage and speed do not matter I will choose vonorability.

ps. I need to probably convert to docs for this. spelling is annoying... but the "low levelness" of an .md file is pretty nice ngl :smirk_face:



### 06/06
I finished all of my TODO's.

finished my_assert with file, func, line and error message.

made test functions for card. 

next on the list is making card_lists in a different file.



### 07/06
Today I will work on cardlist.c and cardlist.h which will contain all functions and structs for the decks. player's hand, dealer's hand and deck.

I made init_cardlist, fill deck, card_remove_at and card_push. 

I need to make card_draw, clear_cardlist, dealer_draw and print-cardlist.


### 10/06
Today TODO: card_draw, clear_cardlist and print-cardlist. as well as any other test functions for cardlists.

did all of the above as well as test_cardlist().

next step: ***initialization of the game***. 

### 14/06
Today TODO: game init, focusing on scaleable architecture and safety.
finished game init in a different file with .h and .c

### 15/06
Today TODO: continue with the game phases, finish functions for game init if needed. 

game init is finished as a function in the game.c/.h files  
bet_phase is finished as a function.  
main code looks really clean!  

for the next day of work on the project I just need to work on the next phases of the game.  
most of the architecture is already layed out, I just need to complete the phases and then I can move on to extra goals!


### 17/06
finished Initial Deal and wrote a bunch of functions.

reset_cards, player_win, black_jack_check, print_hands, hand_value, draw_all(draws all cards from one list to another) and card_value.  
I focused on clean code, writing TODO's when neccasery, styling the game with colors and a lot of testing for all the new functions. 

**What's left?:** 

**DO 2.3 NOW**
1. Hit or Stand & Dealer Draw & Reset Cards (mostly done) phases.
2. Testing  
   > 1. test myself.  
   > 2. send to playtesters (I might need to compile to .exe/.out files).  
   > 3. offer to other students to check each other's code. ***(can ask before)***
3. Polish looks and feel of the game
4. Extra goals!

### 20/06
I finished Hit or Stand.  
Need to do TODO's, they now include safe input handeling with common problems such as buffer overflow.  

### 22/06
Finished Dealer Draw & Reset Cards.  
Need to find a way to skip phases if player wins/loses early game.  
And do a bunch of TODO's

### 26/06  
Found a way to skip phases and put all of the phases into one function so the code in main.c is clean.  
I thought about even taking all the current code in main (malloc, assert, game_init, game_run, game_free) and putting it in another function but that seems a bit over the top.  
Even now when I want to test curtain things the fact that everything is made into a function and not directly in the main code is making it harder.  
But I also think it makes it safer. 

### 27/06
Finished all of my TODO's finally.  
I handled edge cases like:  
- If player wins more then size_t can hold it will not wrap around and player cash = SIZE_MAX.
- Made a way to show negative inputs by scanning to a string and then checking for '-'.  
- I used strtoull with combination with errno to check if the number is bigger then size_t. 

I just got to polish and test now.

### 28/06
There wasn't much to polish and test, although I did fix a couple of small bugs.  
I found another place where there was code repetition so I made it into a function (print_hands_end_game).  
And polish! I added a Yellow color for ties and dealer bust and tested the game some more.  
I'm confident in the safety and functionality of my game and I'm ready to send it out:)  
unfortunatly I didn't have enough time for the Extra goals, but those can remain for later. 

