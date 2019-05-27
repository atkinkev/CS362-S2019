/************************************************************************************
 * Kevin Atkins
 * 5/3/2019
 * unittest2.c
* Positive test for smithy code paths 
* **********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>

int myAssert(int val1, int val2){
	if (val1 != val2){
		return 0;
	}
	else{
		return 1;
	}
}

void testSmithy(){
	struct gameState test;
	struct gameState original;
	int player = -1;
	int choice1 = 1;
	int choice2 = 0;
	int choice3 = 0;
	int choice4 = 0;
	int handpos = 0;
	int bonus[] = {};
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	// Setup case similar to playdom.c
	initializeGame(2, k, 30 , &test);

	// copy over test conditions to saved original conditions so we have the same starting parameters
	memcpy(&original, &test, sizeof(struct gameState));

	// call refactored function with whoever player's turn it is for this random game state
	player = whoseTurn(&test);
	cardEffect(smithy, choice1, choice2, choice3, &test, handpos, bonus);	
        printf("*****************************************************************************\n");
        printf("%s\n", "*************************** BEGIN SMITHY TEST ***************************");
        printf("*****************************************************************************\n");

	/**	TEST 1 - VERIFY 3 CARDS ADDED TO HAND	**/
	printf("%s", "Testing Smithy behavior added 3 cards to hand: ");
	if (myAssert(test.handCount[player], original.handCount[player] + 2) == 1){
		printf("%s\n", "PASS");
	}
	else{
		printf("%s%d%s%d\n", "FAIL - Expected: ", original.handCount[player] + 2, " Actual: ", test.handCount[player]);
	}

	/**	TEST 2 - VERIFY DISCARDED CARD ADDED TO DISCARD	**/
	printf("%s", "Testing Smithy added to discard pile: ");
	if (myAssert(test.discardCount[player], original.discardCount[player] + 1) == 1){
		printf("%s\n", "PASS");
	}
	else{
		 printf("%s%d%s%d\n", "FAIL - Expected: ", original.discardCount[player] + 1, " Actual: ", test.discardCount[player]);
	}
}

int main(){

	testSmithy();
	return 0;

}
