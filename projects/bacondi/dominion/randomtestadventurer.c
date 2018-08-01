/* -----------------------------------------------------------------------
 * Random test for adventurer
 * Expected behavior: used to draw 2 treasure cards into hand
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "myAssert.h"
#include "math.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int adventurerEffect(struct gameState *state);

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

  for (int p = 0; p < G->numPlayers; p++) {
    G->deckCount[p] = random_int(3, MAX_DECK);
    G->handCount[p] = random_int(0, MAX_DECK - G->deckCount[p]);
    G->discardCount[p] = random_int(0, MAX_DECK - G->deckCount[p] - G->handCount[p]);

    // fill hand, deck and discard with random cards
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

int myTest (struct gameState *pre, struct gameState *post)
{
  int numDrawn = 2;
  int numPlayed = 1;

  int numFails = 0;
  int numTests = 0;

  int p = whoseTurn(post);  // only the player whose turn it is has a hand drawn

#ifdef NOISY_TEST
  printf("Test player %d\n", p);
#endif

  numTests += 2;
  numFails += intAssert("player hand count",post->handCount[p], 
    pre->handCount[p] + numDrawn - numPlayed);
  numFails += intAssert("deck + discard count",post->deckCount[p]+post->discardCount[p], 
    pre->deckCount[p]+pre->discardCount[p]+2); 

  // check another player to make sure their hand is unchanged
  if (p < MAX_PLAYERS-1)
    p++;
  else
    p = 0;

#ifdef NOISY_TEST
  printf("Test player %d\n", p);
#endif

  numTests += 3;
  numFails += intAssert("hand count",post->handCount[p], 
    pre->handCount[p]);
  numFails += intAssert("deck count",post->deckCount[p], 
    pre->deckCount[p]); 
  numFails += intAssert("discard count",post->discardCount[p], 
    pre->discardCount[p]); 

  numTests += 2;
  numFails += intAssert("played count",post->playedCardCount, 
    pre->playedCardCount);
  numFails += intAssert("coin count",post->coins, 
    pre->coins);  
  printf("%d of %d tests passed!\n",numTests - numFails, numTests);

  return 0;
}

int main() 
{
  int r,n;
  int handPos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0;

  struct gameState pre,post;

  printf ("TESTING adventurer:\n");

  for (n = 0; n < 1000; n++) {
    printf ("test %d\n",n);
    // randomize initial game state
    r = randomizeGame(&pre);

    // place adventurer in random location in player's hand
    handPos = random_int(0, pre.handCount[pre.whoseTurn]-1);
    pre.hand[pre.whoseTurn][handPos] = adventurer;

    memcpy (&post, &pre, sizeof(struct gameState));

    // make random choices of cardEffect parameters
    bonus = random_int(0, MAX_DECK);
    choice1 = random_int(curse, treasure_map);
    choice2 = random_int(curse, treasure_map);
    choice3 = random_int(curse, treasure_map);

    r = cardEffect(adventurer, choice1, choice2, choice3, &post, handPos, &bonus);
    intAssert("CALLED cardEffect with adventurer",r, 0);
    r = myTest(&pre,&post);
  }

return 0;
}
