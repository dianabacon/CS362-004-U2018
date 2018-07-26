/* -----------------------------------------------------------------------
 * Unit test for mine
 * Trash a Treasure card from your hand. 
 * Gain a Treasure card to your hand costing up to $3 more.
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

int mineEffect(struct gameState *state, int choice1, int choice2, int handPos);

int myTest (struct gameState *pre, struct gameState *post)
{

  int numFails = 0;
  int numTests = 0;

  int p = whoseTurn(pre);  // only the player whose turn it is has a hand drawn

#ifdef NOISY_TEST
  printf("Test player %d\n", p);
#endif

  numTests += 2;
  numFails += intAssert("player hand count",post->handCount[p], 
    pre->handCount[p] );
  numFails += intAssert("deck count",post->deckCount[p], 
    pre->deckCount[p] );

  // show player's hand
#ifdef NOISY_TEST
  printHand(p,pre);
  printHand(p,post);
#endif

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
    pre->playedCardCount );
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

  printf ("TESTING mine:\n");

  // initialize game state
  memset(&pre, 23, sizeof(struct gameState)); 
  memset(&post, 23, sizeof(struct gameState)); 
  r = initializeGame(numPlayer, k, seed, &pre);
  choice1 = 0; // hand# of money to trash
  choice2 = gold; // supply# of money to put in hand (gold)
  post = pre;

  r = cardEffect(mine, choice1, choice2, choice3, &post, handPos, &bonus);
  intAssert("CALLED cardEffect with mine\n",r, 0);
  r = myTest(&pre,&post);

  // initialize game state
  memset(&pre, 23, sizeof(struct gameState)); 
  memset(&post, 23, sizeof(struct gameState)); 
  r = initializeGame(numPlayer, k, seed, &pre);
  choice1 = 0; // hand# of money to trash
  pre.hand[0][choice1] = silver;
  choice2 = copper; // supply# of money to put in hand (bad choice)
  post = pre;

  r = cardEffect(mine, choice1, choice2, choice3, &post, handPos, &bonus);
  intAssert("CALLED cardEffect with mine\n",r, 0);
  r = myTest(&pre,&post);


  // initialize game state
  memset(&pre, 23, sizeof(struct gameState)); 
  memset(&post, 23, sizeof(struct gameState)); 
  r = initializeGame(numPlayer, k, seed, &pre);
  choice1 = 0; // hand# of money to trash
  pre.hand[0][choice1] = gold;
  choice2 = gold; // supply# of money to put in hand (gold)
  post = pre;

  r = cardEffect(mine, choice1, choice2, choice3, &post, handPos, &bonus);
  intAssert("CALLED cardEffect with mine and choice1 = gold\n",r, 0);
  r = myTest(&pre,&post);

  // initialize game state
  memset(&pre, 23, sizeof(struct gameState)); 
  memset(&post, 23, sizeof(struct gameState)); 
  r = initializeGame(numPlayer, k, seed, &pre);
  choice1 = 0; // hand# of money to trash
  pre.hand[0][choice1] = curse;
  choice2 = gold; // supply# of money to put in hand (gold)
  post = pre;

  r = cardEffect(mine, choice1, choice2, choice3, &post, handPos, &bonus);
  intAssert("CALLED cardEffect with mine and choice1 = curse\n",r, 0);
  r = myTest(&pre,&post);

  // initialize game state
  memset(&pre, 23, sizeof(struct gameState)); 
  memset(&post, 23, sizeof(struct gameState)); 
  r = initializeGame(numPlayer, k, seed, &pre);
  choice1 = 0; // hand# of money to trash
  choice2 = curse-1; // supply# of money to put in hand (bad choice)
  post = pre;

  r = cardEffect(mine, choice1, choice2, choice3, &post, handPos, &bonus);
  intAssert("CALLED cardEffect with mine and choice2 < curse\n",r, 0);
  r = myTest(&pre,&post);

  // initialize game state
  memset(&pre, 23, sizeof(struct gameState)); 
  memset(&post, 23, sizeof(struct gameState)); 
  r = initializeGame(numPlayer, k, seed, &pre);
  choice1 = 0; // hand# of money to trash
  choice2 = treasure_map+1; // supply# of money to put in hand (bad choice)
  post = pre;

  r = cardEffect(mine, choice1, choice2, choice3, &post, handPos, &bonus);
  intAssert("CALLED cardEffect with mine and choice2 > treasure_map\n",r, 0);
  r = myTest(&pre,&post);

  // initialize game state
  memset(&pre, 23, sizeof(struct gameState)); 
  memset(&post, 23, sizeof(struct gameState)); 
  r = initializeGame(numPlayer, k, seed, &pre);
  choice1 = 0; // hand# of money to trash
  choice2 = 6; // supply# of money to put in hand (gold)
  post = pre;

  r = mineEffect(&post, choice1, choice2, handPos);
  intAssert("CALLED mineEffect\n",r, 0);
  r = myTest(&pre,&post);

return 0;
}
