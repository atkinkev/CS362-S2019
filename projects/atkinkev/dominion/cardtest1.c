/************************************************************************************
 ** Kevin Atkins
 ** 5/3/2019
 ** cardtest.c
 ** Boundary tests for Steward
 ** **********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <limits.h>
#include <string.h>

int myAssert(int val1, int val2){
        if (val1 != val2){
                return 0;
        }
        else{
                return 1;
        }
}

void testSteward(){
        struct gameState test;
	struct gameState original;
	//int player = -1;
	int choice1 = 1;
	int choice2 = 0;
	int choice3 = 0;
	int handpos = 0;
	int bonus[] = {};
	int k[10] = {adventurer, steward, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
        
	// init test game and copy test params to original
	initializeGame(2, k, 30, &test);
	memcpy(&original, &test, sizeof(struct gameState));
	//player = whoseTurn(&test);
	
	// testing Steward with initial coins = INT_MAX	
	test.coins = INT_MAX;
	original.coins = INT_MAX;
	choice1 = 2;
	cardEffect(18, choice1, choice2, choice3, &test, handpos, bonus); 

        printf("*****************************************************************************\n");
        printf("%s\n", "*************************** BEGIN STEWARD TEST ***************************");
        printf("*****************************************************************************\n");
		
	printf("%s", "Testing Steward card with coins at INT_MAX: ");
	if(myAssert(test.coins, original.coins) == 0){
		printf("%s\n","FAIL - Integer addition at INT_MAX unhandled.");
	}
	else{
		printf("%s\n", "PASS: Integer overflow prevented.");
	}
}

int main(){
	testSteward();
	return 0;
}
