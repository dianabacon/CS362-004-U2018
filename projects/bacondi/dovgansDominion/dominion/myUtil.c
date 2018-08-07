/* ----------------------------------------------------------------------- 
 * Name            : myUtil.c 
 * Author          : Diana Bacon
 * Language        : ANSI C
 * Description     : Utility functions for random testing
 * ----------------------------------------------------------------------- 
 */

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "myAssert.h"
#include "math.h"

// generate random number in range min to max-1
int random_int(int min, int max) 
{
  return min + (max - min)*(double)rand()/(double)RAND_MAX;
}

// randomly initialize the game state
int randomizeGame(struct gameState *G) 
{
  // start with completely random game state
  for (int i = 0; i < (int)sizeof(struct gameState); i++) {
    ((char*)G)[i] = floor(Random() * 256);
  }

  // randomize sizes within reasonable ranges
  G->numPlayers = random_int(2, MAX_PLAYERS);
  G->whoseTurn = random_int(0, G->numPlayers);
  G->playedCardCount = 0;

    // fill deck, hand and discard with random cards
  for (int p = 0; p < G->numPlayers; p++) {
    G->deckCount[p] = random_int(3, MAX_DECK);
    G->handCount[p] = random_int(0, MAX_DECK - G->deckCount[p]);
    G->discardCount[p] = random_int(0, MAX_DECK - G->deckCount[p] - G->handCount[p]);

    for (int i = 0; i < G->deckCount[p]; i++)
      G->deck[p][i] = random_int(curse, treasure_map);
    for (int i = 0; i < G->handCount[p]; i++)
      G->hand[p][i] = random_int(curse, treasure_map);
    for (int i = 0; i < G->discardCount[p]; i++)
      G->discard[p][i] = random_int(curse, treasure_map);
    updateCoins(p, G, 0); 
  }

  return 0;
}

