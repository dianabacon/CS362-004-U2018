/* -----------------------------------------------------------------------
 * Unit test for smithy
 * Expected behavior: draw 3 cards into hand
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
#include "myUtil.h"

int numFails = 0;
int numTests = 0;

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int smithyEffect(struct gameState *state, int handPos);

int myTest (struct gameState *pre, struct gameState *post)
{
  int numDrawn = 3;
  int numPlayed = 1;

  int p = whoseTurn(pre);  // only the player whose turn it is has a hand drawn

#ifdef NOISY_TEST
  printf("Test player %d\n", p);
#endif

  numTests += 2;
  numFails += intAssert("player hand count",post->handCount[p], 
    pre->handCount[p] + numDrawn - numPlayed);
  numFails += intAssert("deck count",post->deckCount[p], 
    pre->deckCount[p] - numDrawn);

  // check another player to make sure their hand is unchanged
  if (p < pre->numPlayers-1)
    p++;
  else
    p = 0;

#ifdef NOISY_TEST
  printf("Test opponent %d\n", p);
#endif

  numTests += 2;
  numFails += intAssert("hand count",post->handCount[p], 
    pre->handCount[p]);
  numFails += intAssert("deck count",post->deckCount[p], 
    pre->deckCount[p]);

  numTests += 2;
  numFails += intAssert("played count",post->playedCardCount, 
    pre->playedCardCount + numPlayed);
  numFails += intAssert("coin count",post->coins, 
    pre->coins);


  printf("%d of %d tests passed!\n",numTests - numFails, numTests);

  return 0;
}

int main() {
  int r,n;
  int handPos, choice1, choice2, choice3, bonus;

  struct gameState pre, post;

  printf ("TESTING smithy:\n");  

  for (n = 0; n < 1000; n++) {
    printf ("test %d\n",n);
    // randomize initial game state
    r = randomizeGame(&pre);

    // place smithy in random location in player's hand
    handPos = random_int(0, pre.handCount[pre.whoseTurn]-1);
    pre.hand[pre.whoseTurn][handPos] = smithy;

    // make random choices of cardEffect parameters
    bonus = random_int(0, MAX_DECK);
    choice1 = random_int(curse, treasure_map);
    choice2 = random_int(curse, treasure_map);
    choice3 = random_int(curse, treasure_map);

    memcpy (&post, &pre, sizeof(struct gameState));
    r = cardEffect(smithy, choice1, choice2, choice3, &post, handPos, &bonus);
    intAssert("CALLED cardEffect with smithy\n",r, 0);
    r = myTest(&pre,&post);

//    memcpy (&post, &pre, sizeof(struct gameState));
//    r = smithyEffect(&post, handPos);
//    intAssert("CALLED smithyEffect\n",r, 0);
//    r = myTest(&pre,&post);
  }
  printf("%d of %d tests passed!\n",numTests - numFails, numTests);

return 0;
}
