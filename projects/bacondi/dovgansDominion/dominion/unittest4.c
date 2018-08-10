/* -----------------------------------------------------------------------
 * Unit test for discardCard
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
  int p, trashFlag, discardCount, handPos;
  int seed = 1000;
  int numPlayer = 2;
  int numDiscard = 5;
  int handCount = 5;
  int numSupply = 10;
  int numCards = 27;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
   remodel, smithy, village, baron, great_hall};

   struct gameState G;

   int numFails = 0;
   int numTests = 0;

   printf ("TESTING discardCard():\n");
   for (p = 0; p < numPlayer; p++) {
     for (discardCount = 0; discardCount < numDiscard; discardCount++) {
        for (handPos = 0; handPos < handCount; handPos++) {
          for (trashFlag = 0; trashFlag <= 1; trashFlag++) {
#if (NOISY_TEST == 1)
            printf("Test player %d with %d in discard and %d in hand.\n", p, discardCount, handPos);
#endif

            // initialize game state
            memset(&G, 23, sizeof(struct gameState)); 
            initializeGame(numPlayer, k, seed, &G);
            G.discardCount[p] = discardCount;
            memset(G.discard[p], 0, sizeof(int) * discardCount);
            G.handCount[p] = handCount;
            memset(G.hand[p], 0, sizeof(int) * handCount);
            for(int i = 0; i < numCards; i++){
              G.supplyCount[i] = numSupply;
            }

            numTests += 2;

            if (trashFlag < 1){
              discardCard(handPos, p, &G, trashFlag);
              numFails += intAssert("G.discardCount",G.discardCount[p], discardCount + 1); // check if the discard size is correct
              numFails += intAssert("G.handCount",G.handCount[p], handCount - 1); // check if the hand size is correct
            } else {
              discardCard(handPos, p, &G, trashFlag);
              numFails += intAssert("G.discardCount",G.discardCount[p], discardCount); // check if the discard size is correct
              numFails += intAssert("G.handCount",G.handCount[p], handCount - 1); // check if the hand size is correct
            }

      }
    }
  }
}

printf("%d of %d tests passed!\n",numTests - numFails, numTests);

return 0;
}
