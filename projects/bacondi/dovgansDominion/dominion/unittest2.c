/* -----------------------------------------------------------------------
 * Unit test for drawCard
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

int main() {
  int p, deckCount, discardCount, handCount;
  int seed = 1000;
  int numPlayer = 2;
  int numDeck = 5;
  int numDiscard = 5;
  int numHand = 5;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};

  struct gameState G;

  int numFails = 0;
  int numTests = 0;

  printf ("TESTING drawCard():\n");
  for (p = 0; p < numPlayer; p++) {
    for (deckCount = 0; deckCount < numDeck; deckCount++) {
      for (discardCount = 0; discardCount < numDiscard; discardCount++) {
        for (handCount = 0; handCount < numHand; handCount++) {
#if (NOISY_TEST == 1)
          printf("Test player %d with %d in deck %d in discard and %d in hand.\n", p, deckCount, discardCount, handCount);
#endif
          memset(&G, 23, sizeof(struct gameState)); 
          initializeGame(numPlayer, k, seed, &G);
          G.deckCount[p] = deckCount;
          memset(G.deck[p], 0, sizeof(int) * deckCount);
          G.discardCount[p] = discardCount;
          memset(G.discard[p], 0, sizeof(int) * discardCount);
          G.handCount[p] = handCount;
          memset(G.hand[p], 0, sizeof(int) * handCount);

          drawCard (p, &G);

          numTests += 3;

          if (deckCount > 0) {
            numFails += intAssert("G.deckCount",G.deckCount[p], deckCount - 1); // check if the deck size is correct
            numFails += intAssert("G.discardCount",G.discardCount[p], discardCount); // check if the discard size is correct
            numFails += intAssert("G.handCount",G.handCount[p], handCount + 1); // check if the hand size is correct

          } else if (discardCount > 0) {
            numFails += intAssert("G.deckCount",G.deckCount[p], discardCount - 1); // check if the deck size is correct
            numFails += intAssert("G.discardCount",G.discardCount[p], 0); // check if the discard size is correct
            numFails += intAssert("G.handCount",G.handCount[p], handCount + 1); // check if the hand size is correct

          } else {
            numFails += intAssert("G.deckCount",G.deckCount[p], 0); // check if the deck size is correct
            numFails += intAssert("G.discardCount",G.discardCount[p], 0); // check if the discard size is correct
            numFails += intAssert("G.handCount",G.handCount[p], handCount); // check if the hand size is correct           
          }
         
        }
      }
    }
  }

  printf("%d of %d tests passed!\n",numTests - numFails, numTests);

  return 0;
}
