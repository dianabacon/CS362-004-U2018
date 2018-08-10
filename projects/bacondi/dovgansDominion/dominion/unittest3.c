/* -----------------------------------------------------------------------
 * Unit test for gainCard
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
  int numSupply = 10;
  int numCards = 27;
  int toFlag;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
   remodel, smithy, village, baron, great_hall};

   struct gameState G;

   int numFails = 0;
   int numTests = 0;

   printf ("TESTING gainCard():\n");
   for (p = 0; p < numPlayer; p++) {
     for (discardCount = 0; discardCount < numDiscard; discardCount++) {
      for (deckCount = 0; deckCount < numDeck; deckCount++) {
          for (handCount = 0; handCount < numHand; handCount++) {
#if (NOISY_TEST == 1)
            printf("Test player %d with %d in discard %d in deck and %d in hand.\n", p, discardCount, deckCount, handCount);
#endif

            // initialize game state
            memset(&G, 23, sizeof(struct gameState)); 
            initializeGame(numPlayer, k, seed, &G);
            G.deckCount[p] = deckCount;
            memset(G.deck[p], 0, sizeof(int) * deckCount);
            G.discardCount[p] = discardCount;
            memset(G.discard[p], 0, sizeof(int) * discardCount);
            G.handCount[p] = handCount;
            memset(G.hand[p], 0, sizeof(int) * handCount);
            for(int i = 0; i < numCards; i++){
              G.supplyCount[i] = numSupply;
            }

            numTests += 3;

            toFlag = 0; // add to discard
            gainCard(numSupply, &G, toFlag, p);
            numFails += intAssert("G.discardCount",G.discardCount[p], discardCount + 1); // check if the discard size is correct

            toFlag = 1; // add to deck
            gainCard(numSupply, &G, toFlag, p);
            numFails += intAssert("G.deckCount",G.deckCount[p], deckCount + 1); // check if the deck size is correct

            toFlag = 2; // add to hand
            gainCard(numSupply, &G, toFlag, p);
            numFails += intAssert("G.handCount",G.handCount[p], handCount + 1); // check if the hand size is correct
      }
    }
  }
}

printf("%d of %d tests passed!\n",numTests - numFails, numTests);

return 0;
}
