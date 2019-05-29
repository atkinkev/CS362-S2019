/************************************************************************************
 * Kevin Atkins
 * 5/3/2019
 * unittest3.c
 * Positive Tests for Buy Cards
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

void testVillage(){
	struct gameState test;
	struct gameState original;
	int handpos = 0;
        int player = -1;
        int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int bonus[] = {};
	
	initializeGame(2, k, 30, &test);
	drawCard(player, &test);
        drawCard(player, &test);
        drawCard(player, &test);

	memcpy(&original, &test, sizeof(struct gameState));
	player = whoseTurn(&test);
	
	cardEffect(village, 0, 0, 0, &test, handpos, bonus); 	

        printf("*****************************************************************************\n");
        printf("%s\n", "*************************** BEGIN VILLAGE TEST ***************************");
        printf("*****************************************************************************\n");


	printf("%s", "Testing proper number of actions after playing Village: ");
	if (myAssert(test.numActions, original.numActions + 2) == 1){
		printf("%s\n", "PASS");  
	}
	else{
		printf("%s\n", "FAIL");
	}
	
	printf("%s", "Testing proper number of cards in hand after playing Village: ");
        if (myAssert(test.handCount[player], original.handCount[player]) == 1){
                printf("%s\n", "PASS");
        }
        else{
                printf("%s\n", "FAIL");
        }

	printf("%s", "Testing proper number of cards in deck after playing Village: ");
	if (myAssert(test.deckCount[player], original.deckCount[player] - 1) == 1){
                printf("%s\n", "PASS");
        }
        else{
                printf("%s\n", "FAIL");
        }
}

int main(){
	testVillage();
	return 0;

}
