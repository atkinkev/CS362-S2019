/************************************************************************************
 ** Kevin Atkins
 ** 5/3/2019
 ** cardtest.c
 ** Positive tests for Council Room
 ** **********************************************************************************/
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

void testCouncilRoom(){
        struct gameState test;
        struct gameState original;
	int i = 0;
	int player = -1;
	int choice1 = 1;
	int k[10] = {adventurer, steward, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
        
	initializeGame(4, k, 30, &test);
	memcpy(&original, &test, sizeof(struct gameState));
	player = whoseTurn(&test);
	
	council_roomEffect(player, &test, 0);

        printf("*****************************************************************************\n");
        printf("%s\n", "*************************** BEGIN COUNCIL_ROOM TEST ***************************");
        printf("*****************************************************************************\n");

	
	printf("Testing gain of 4 cards and 1 discard after playing Council Room: ");	
	if (myAssert(test.handCount[player], original.handCount[player]+ 3) == 1){
		printf("%s\n", "PASS");
	}
	else{
		printf("%s%d%s%d\n", "FAIL - Expected ", original.handCount[player] + 3, " cards. Actual: ", test.handCount[player] );
	}
	
	printf("Testing gain of 1 card for all other players: ");
	for(i = 0; i < test.numPlayers; i++){
		if (i == player){
			continue;
		}
		else if (myAssert(test.handCount[i], original.handCount[i] + 1) == 0){
			printf("%s%d%s%d%s%d\n", "FAIL - Expected ", original.handCount[i] + 1, " cards for player ", i+1,". Actual: ", test.handCount[i]);
			break;
		}
		else if (i == test.numPlayers - 1){
			printf("%s\n", "PASS");
		}
	}
}

int main(){
	testCouncilRoom();
	return 0;
}
