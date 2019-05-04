/************************************************************************************
 * Kevin Atkins
 * 5/3/2019
 * unittest1.c
 * Purpose: Determine that each flag value is sent to the proper place (deck/hand/discard)
 * **********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"
#include <string.h>

int myAssert(int val1, int val2){
	if (val1 == val2){
		return 1;
	}
	else{
		return 0;
	}
}

void testGainCard(){
	struct gameState test;
	struct gameState expected;
	int player = 0;
	int returnVal = -1;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};	
	initializeGame(2, k, 30, &test);
	memcpy(&expected, &test, sizeof(struct gameState));
	
	/***	Determine Cards are Sent to Proper Place	***/

	printf("*****************************************************************************\n");
	printf("%s\n", "*************************** BEGIN gainCard() TEST ***************************");	
	printf("*****************************************************************************\n");
	// DISCARD	
	gainCard(0, &test, 0, player);
	printf("%s", "Test gainCard with flag 0 is sent to discard: ");
	if (myAssert(test.discardCount[player], expected.discardCount[player] + 1)){
		printf("%s\n", "PASS");
	}
	else{
		printf("%s\n", "FAIL");
	}

	// DECK
	gainCard(0, &test, 1, player);
	printf("%s", "Test gainCard with flag 1 is sent to deck: ");	
        if (myAssert(test.deckCount[player], expected.deckCount[player] + 1)){
                printf("%s\n", "PASS");
        }
        else{
                printf("%s\n", "FAIL");
        }
	
	// HAND
	gainCard(0, &test, 2, player);
	printf("%s", "Test gainCard with flag 2 is sent to hand: ");	
        if (myAssert(test.handCount[player], expected.handCount[player] + 1)){
                printf("%s\n", "PASS");
        }
        else{
                printf("%s\n", "FAIL");
     	}

	// UNKNOWN
	returnVal = gainCard(0, &test, -1, player);
	printf("%s", "Testing gainCard with unsupported flag doesn't crash: ");
	if (myAssert(returnVal, 0) == 1){
                printf("%s\n", "PASS");
        }
        else{
                printf("%s\n", "FAIL");
        }


}
int main(){

	testGainCard();
}
