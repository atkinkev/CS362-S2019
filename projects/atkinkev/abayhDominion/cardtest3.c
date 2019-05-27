/************************************************************************************
 * Kevin Atkins
 * 5/3/2019
 * Negative tests for Remodel
 * **********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <limits.h>

int myAssert(int val1, int val2){
	if (val1 != val2){
		return 0;
	}
	else{
		return 1;
	}
}

void testRemodel(){
	struct gameState test;
	struct gameState expected;
	int player = -1;
	int choice1, choice2, choice3 = 0;
	int handpos = 0;
	int bonus[] = {};
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	// Setup case similar to playdom.c
	initializeGame(2, k, 30 , &test);

	// copy over test conditions to expected conditions so we have the same starting parameters
	memcpy(&expected, &test, sizeof(struct gameState));

	// call refactored function with whoever player's turn it is for this random game state
	player = whoseTurn(&test);
	
	choice1 = -1;
	choice2 = -1;
	cardEffect(remodel, choice1, choice2, choice3, &test, handpos, bonus);
	
        printf("*****************************************************************************\n");
        printf("%s\n", "*************************** BEGIN REMODEL TEST ***************************");
        printf("*****************************************************************************\n");
	
	/**	TEST 1 - VERIFY CHOICES OUT OF INDEX RANGE DON'T CRASH	**/
	printf("%s", "Testing choice1 and choice2 outside of array index range doesn't crash and no changes are made: ");
	if (myAssert(test.handCount[player], expected.handCount[player]) == 1){
		printf("%s\n", "PASS");
	}
	else{
		printf("%s\n", "FAIL");
	}

	/**	TEST 2 - VERIFY CHOICES OUT OF CURRENT GAMEPLAY RANGE	**/
	choice1 = test.handCount[player] + 5;
	choice2 = 0;
	cardEffect(remodel, choice1, choice2, choice3, &test, handpos, bonus);
	printf("%s", "Testing trash card choice outside of hand range doesn't crash and no changes are made: ");
	if (myAssert(test.discardCount[player], expected.discardCount[player]) == 1){
		printf("%s\n", "PASS");
	}
	else{
		printf("%s\n", "FAIL");
	}
}

int main(){

	testRemodel();
	return 0;

}
