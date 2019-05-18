/**********************************************************************************************************
 * Kevin Atkins
 * 5/6/2019
 * randomtestcard1.c
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

void randomRemodelTest(){
        struct gameState test;
        struct gameState original;
	int choiceInDeck = 0;
	int choiceInDeckPost = 0;
        int player = 0;
        int choice1 = 0;
        int choice2 = 0;
        int choice3 = 0;
        int handpos = 0;
	int deckSize = 0;
	int handSize = 0;
        int bonus[] = {};
	int cardDrawn;
	int cost1, cost2 = 0;
	int i,j= 0;
	int tCountFails = 0;
	int k[10] = {adventurer, steward, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};


        printf("\n\n*****************************************************************************\n");
        printf("%s\n", "*************************** BEGIN REMODEL TEST ***************************");
	printf("*****************************************************************************\n");
	
	srand(time(0));

	for (i = 0; i < 100000; i++){
		initializeGame(2, k, 30, &test);
		player = whoseTurn(&test);
		
		deckSize = rand() % MAX_DECK + 1;
		handSize = rand() % deckSize + 1;
	
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
			
		choice1 = rand() % test.handCount[player];
		choice2 = rand() % 28;
		choiceInDeck = 0;
		for(j = 0; j < test.deckCount[player]; j++){
			if (test.deck[player][j] == choice2){
				choiceInDeck++;
			}
		}
	
		handpos = test.hand[player][test.handCount[player] - 1];	
		memcpy(&original, &test, sizeof(struct gameState));
		
		cardEffect(remodel, choice1, choice2, choice3, &test, handpos, bonus);	
		
		choiceInDeckPost = 0;
                for(j = 0; j < test.deckCount[player]; j++){
                        if (test.deck[player][j] == choice2){
                                choiceInDeckPost++;
                        }
                }

		if (getCost(choice1) + 2 <= getCost(choice2)) {
			if (myAssert(choiceInDeckPost, choiceInDeck + 1) == 0){
				if (tCountFails < 11){
					printf("%s%d%s%d\n","FAIL: Valid choice not added to deck. Expected choice2 cards in deck: ", choiceInDeck + 1, " Actual: ", choiceInDeckPost);	
				}	
				tCountFails++;
			}
			if (tCountFails == 11){
				printf("More than 10 fails recorded for this test. See end of test totals for total counts.\n");
			}
		}
	}

	printf("\n**** END OF TEST TOTALS ****\n");
	printf("%s%d\n", "Chosen Card Discrepancies: ", tCountFails); 	
	
}

int main(){
	randomRemodelTest();
	return 0;
}
