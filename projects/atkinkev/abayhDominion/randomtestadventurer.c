/**********************************************************************************************************
 * Kevin Atkins
 * 5/6/2019
 * randomtestadventurer.c
 * *******************************************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

int myAssert(int val1, int val2){
        if (val1 != val2){
                return 0;
        }
        else{
                return 1;
        }
}

void randomAdventurerTest(){
        struct gameState test;
        struct gameState original;
	int treasureFound = 0;
	int treasureExpected = 0;
        int player = 0;
        int choice1 = 0;
        int choice2 = 0;
        int choice3 = 0;
        int handpos = 0;
	int deckSize = 0;
	int handSize = 0;
        int bonus[] = {};
	int cardDrawn;
	int i,j= 0;
	int tCountFails = 0;
	int k[10] = {adventurer, steward, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};


        printf("\n\n*****************************************************************************\n");
        printf("%s\n", "*************************** BEGIN ADVENTURER TEST ***************************");
	printf("*****************************************************************************\n");
	
	srand(time(0));

	for (i = 0; i < 100000; i++){
		initializeGame(2, k, 30, &test);
		player = whoseTurn(&test);
		
		deckSize = rand() % (MAX_DECK + 1);
		handSize = rand() % (deckSize + 1);
	
		test.deckCount[player] = deckSize - handSize;
		test.handCount[player] = handSize;

		// randomize deck (initialized to curse)
		for(j = 0; j < test.deckCount[player]; j++){
			if (test.deck[player][j] == curse){
				test.deck[player][j] = rand() % 28;
			}
		}
	
		// randomize hand
	        for(j = 0; j < test.handCount[player]; j++){
	                if (test.hand[player][j] == curse){
	                        test.hand[player][j] = rand() % 28;
	                }
	        }
	
		handpos = test.hand[player][test.handCount[player] - 1];	
		memcpy(&original, &test, sizeof(struct gameState));
	
		cardEffect(adventurer, choice1, choice2, choice3, &test, handpos, bonus);
		
		treasureFound = 0;
		treasureExpected = 0;

		// treasure found in test hand
	        for (j = 0; j < test.handCount[player]; j++){
	                cardDrawn = test.hand[player][j];
        	        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
                	        treasureFound++;
                	}
		}

		for (j = 0; j < original.handCount[player]; j++){
			cardDrawn = original.hand[player][j];
	                if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
                                treasureExpected++;
                        }
                }

		if (myAssert(treasureFound, treasureExpected + 2) == 0){
			if (tCountFails < 10){
				printf("%s%d%s%d\n", "FAIL -- Expected Treasure: ", treasureExpected + 2, " Actual: ", treasureFound);
			}
			else if (tCountFails == 10){
				printf("%s", "More than 10 treasure discrepancies. See end of log for total failures.\n");
			}
			tCountFails++;
		}
	}

	printf("\n**** END OF TEST TOTALS ****\n");
	printf("%s%d\n\n\n", "Treasure Discrepancies: ", tCountFails); 	
	
}

int main(){
	randomAdventurerTest();
	return 0;
}
