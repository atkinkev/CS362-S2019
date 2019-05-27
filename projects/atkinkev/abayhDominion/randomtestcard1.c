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
	int i,j= 0;
	int tCountFails = 0;
	int dcCountFails = 0;
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
		for(j = 0; j < test.discardCount[player]; j++){
			if (test.discard[player][j] == choice2){
				choiceInDeck++;
			}
		}
	
		handpos = test.hand[player][test.handCount[player] - 1];	
		memcpy(&original, &test, sizeof(struct gameState));
		
		cardEffect(remodel, choice1, choice2, choice3, &test, handpos, bonus);	
		
		choiceInDeckPost = 0;
                for(j = 0; j < test.discardCount[player]; j++){
                        if (test.discard[player][j] == choice2){
                                choiceInDeckPost++;
                        }
                }

		if (getCost(choice2) <= getCost(choice1) + 2) {
			if (myAssert(choiceInDeckPost, choiceInDeck + 1) == 0){
				if (tCountFails < 11){
					printf("%s%d%s%d\n","FAIL: Valid choice not added to discard. Expected choice2 cards in discard: ", choiceInDeck + 1, " Actual: ", choiceInDeckPost);	
				}	
				tCountFails++;
			}
			if (tCountFails == 11){
				printf("More than 10 fails recorded for finding choice2 in discard. See end of test totals for total counts.\n");
			}
			
			if (myAssert(test.discardCount[player], original.discardCount[player] + 3) == 0 && test.handCount[player] > 3){
				if (dcCountFails < 10){
					printf("%s%d%s%d\n","FAIL: Discard count not accurate. Expected: ", original.discardCount[player] + 3, " Actual: ", test.discardCount[player]);
				}
				dcCountFails++;
				if (dcCountFails == 10){
					printf("More than 10 fails recorded for discard count checking. See end of totals for total counts.\n");
				}
			}
		}
		

		
	}

	printf("\n**** END OF TEST TOTALS ****\n");
	printf("%s%d\n", "Chosen Card not added to Discard Fails: ", tCountFails); 
	printf("%s%d\n", "Test proper number of cards added to discard fails: ", dcCountFails);	
	
}

int main(){
	randomRemodelTest();
	return 0;
}
