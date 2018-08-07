/* -----------------------------------------------------------------------
 * Unit test for sea_hag
 * Expected behavior: Each other player discards the top card of their  
 * deck, then adds a Curse card to the top of their deck.
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
#include "interface.h"
#include "myUtil.h"

int numFails = 0;
int numTests = 0;

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int sea_hagEffect(struct gameState *state);

int myTest (struct gameState *pre, struct gameState *post)
{

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

  // check another player to make sure their hand is unchanged
  if (p < pre->numPlayers-1)
    p++;
  else
    p = 0;

#ifdef NOISY_TEST
  printf("Test opponent %d\n", p);
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
  int r,n;
  int handPos, choice1, choice2, choice3, bonus;

  struct gameState pre, post;
  printf ("TESTING sea_hag:\n");

  for (n = 0; n < 1000; n++) {
    printf ("test %d\n",n);
    // randomize initial game state
    r = randomizeGame(&pre);

    // place sea_hag in random location in player's hand
    handPos = random_int(0, pre.handCount[pre.whoseTurn]-1);
    pre.hand[pre.whoseTurn][handPos] = sea_hag;

    // make random choices of cardEffect parameters
    bonus = random_int(0, MAX_DECK);
    choice1 = random_int(curse, treasure_map);
    choice2 = random_int(curse, treasure_map);
    choice3 = random_int(curse, treasure_map);

    memcpy (&post, &pre, sizeof(struct gameState));
    r = cardEffect(sea_hag, choice1, choice2, choice3, &post, handPos, &bonus);
    intAssert("CALLED cardEffect with sea_hag\n",r, 0);
    r = myTest(&pre,&post);

    memcpy (&post, &pre, sizeof(struct gameState));
    r = sea_hagEffect(&post);
    intAssert("CALLED sea_hagEffect\n",r, 0);
    r = myTest(&pre,&post);
  }
  printf("%d of %d tests passed!\n",numTests - numFails, numTests);

return 0;
}
