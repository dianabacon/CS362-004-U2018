/* -----------------------------------------------------------------------
 * Unit test for smithy
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "myAssert.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

//int smithyEffect(struct gameState *state, int handPos);
int smithyCardEffect(struct gameState *state, const int currentPlayer, const int handPos);

int myTest (struct gameState *pre, struct gameState *post)
{
  int numDrawn = 3;
  int numPlayed = 1;

  int numFails = 0;
  int numTests = 0;

  int p = whoseTurn(pre);  // only the player whose turn it is has a hand drawn

#ifdef NOISY_TEST
  printf("Test player %d\n", p);
#endif

  numTests += 2;
  numFails += intAssert("player hand count",post->handCount[p], 
    pre->handCount[p] + numDrawn - numPlayed);
  numFails += intAssert("deck count",post->deckCount[p], 
    pre->deckCount[p] - numDrawn);

  p++;
#ifdef NOISY_TEST
  printf("Test player %d\n", p);
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
  int r;
  int handPos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0;
  int seed = 1000;
  int numPlayer = 2;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
   remodel, smithy, village, baron, great_hall};

  struct gameState pre, post;

  printf ("TESTING smithy:\n");  

  // initialize game state
  memset(&pre, 23, sizeof(struct gameState)); 
  memset(&post, 23, sizeof(struct gameState)); 
  r = initializeGame(numPlayer, k, seed, &pre);
  post = pre;

  r = cardEffect(smithy, choice1, choice2, choice3, &post, handPos, &bonus);
  intAssert("CALLED cardEffect with smithy\n",r, 0);
  r = myTest(&pre,&post);

  // initialize game state
  memset(&pre, 23, sizeof(struct gameState)); 
  memset(&post, 23, sizeof(struct gameState)); 
  r = initializeGame(numPlayer, k, seed, &pre);
  post = pre;

//  r = smithyCardEffect(&post, whoseTurn(&post), handPos);
//  intAssert("CALLED smithyEffect\n",r, 0);
//  r = myTest(&pre,&post);

return 0;
}
