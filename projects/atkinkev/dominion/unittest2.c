/************************************************************************************
 * Kevin Atkins
 * 5/3/2019
 * unittest2.c
 * Purpose: Determine that endTurn properly passes off the turn to the next proper player. 
 * **********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include <string.h>

int myAssert(int val1, int val2){
	if (val1 != val2){
		return 0;
	}
	else{
		return 1;
	}
}

// test endTurn() function for proper 
void testEndTurn(){
	struct gameState G;
	int player = -1;
	int numPlayers = 2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	initializeGame(numPlayers, k, 30, &G);
	G.whoseTurn = 0;
	player = 0;

	endTurn(&G);

        printf("*****************************************************************************\n");
        printf("%s\n", "*************************** BEGIN endTurn() TEST ***************************");
        printf("*****************************************************************************\n");

		
	printf("%s", "Testing that it is player 2's turn after player 1 ends their turn: ");
	if (myAssert(G.whoseTurn, player + 1) == 1){
		printf("%s\n", "PASS");
	}
	else{
		printf("%s\n", "FAIL");
	}

	endTurn(&G);

	printf("%s", "Testing that it is player 1's turn after player 2 ends their turn (2 player game): ");
        if (myAssert(G.whoseTurn, player) == 1){
                printf("%s\n", "PASS");
        }
        else{
                printf("%s\n", "FAIL");
        }	
}

int main(){
	testEndTurn();
	return 0;
}
