/* -----------------------------------------------------------------------
 * Unit test for sea_hag
 * Each other player discards the top card of their deck, then adds a 
 * Curse card to the top of their deck.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "myAssert.h"
#include "interface.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int sea_hagEffect(struct gameState *state);

int myTest (struct gameState *pre, struct gameState *post)
{
  int numFails = 0;
  int numTests = 0;

  int p = whoseTurn(pre);  // only the player whose turn it is has a hand drawn

#ifdef NOISY_TEST
  printf("Test player %d\n", p);
#endif

  numTests += 3;
  numFails += intAssert("player hand count",post->handCount[p], 
    pre->handCount[p] );
  numFails += intAssert("deck count",post->deckCount[p], 
    pre->deckCount[p]);
  numFails += intAssert("discard count",post->discardCount[p], 
    pre->discardCount[p]);
  p++;
#ifdef NOISY_TEST
  printf("Test player %d\n", p);
#endif

  numTests += 3;
  numFails += intAssert("hand count",post->handCount[p], 
    pre->handCount[p]);
  numFails += intAssert("deck count",post->deckCount[p], 
    pre->deckCount[p]);
  numFails += intAssert("discard count",post->discardCount[p], 
    pre->discardCount[p] + 1);

  numTests += 2;
  numFails += intAssert("played count",post->playedCardCount, 
    pre->playedCardCount );
  numFails += intAssert("coin count",post->coins, 
    pre->coins);

  printf("%d of %d tests passed!\n",numTests - numFails, numTests);

  return 0;
}

int main() {
  int r;
  int handPos = 0, choice1 =-1, choice2 =-1, choice3 = -1, bonus = 0;
  int seed = 1000;
  int numPlayer = 2;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
   remodel, smithy, village, baron, great_hall};

  struct gameState pre, post;
  printf ("TESTING sea_hag:\n");

  // initialize game state
  memset(&pre, 23, sizeof(struct gameState)); 
  memset(&post, 23, sizeof(struct gameState)); 
  r = initializeGame(numPlayer, k, seed, &pre);
  post = pre;

  r = cardEffect(sea_hag, choice1, choice2, choice3, &post, handPos, &bonus);
  intAssert("CALLED cardEffect with sea_hag\n",r, 0);
  r = myTest(&pre,&post);

  // initialize game state
  memset(&pre, 23, sizeof(struct gameState)); 
  memset(&post, 23, sizeof(struct gameState)); 
  r = initializeGame(numPlayer, k, seed, &pre);
  post = pre;

  r = sea_hagEffect(&post);
  intAssert("CALLED sea_hagEffect\n",r, 0);
  r = myTest(&pre,&post);

return 0;
}
