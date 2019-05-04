 /***********************************************************************************
 ** 5/3/2019
 ** cardtest.c
 ** Negative tests for adventurer
 ** **********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
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

void testAdventurer(){
        struct gameState test;
        struct gameState original;
        int player = -1;
        int choice1 = 1;
        int choice2 = 0;
        int choice3 = 0;
        int handpos = 0;
        int bonus[] = {};
	int cardDrawn;
	int i = 0;
        int k[10] = {adventurer, steward, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

        // init test game and copy test params to original
        initializeGame(2, k, 30, &test);
        memcpy(&original, &test, sizeof(struct gameState));
	player = whoseTurn(&test);

        printf("*****************************************************************************\n");
        printf("%s\n", "*************************** BEGIN ADVENTURER TEST ***************************");
        printf("*****************************************************************************\n");

	/***	TEST1 - TEST ADVENTURER CARD WITH 2+ TREASURE CARDS IN DECK	***/
        // fill deck with treasure
	for (i = 0; i < test.deckCount[player]; i++){
                test.deck[player][i] = copper;
        }
	
	// empty hand of treasure
        for (i = 0; i < test.handCount[player]; i++){
                cardDrawn = test.hand[player][i];
                if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
                        test.hand[player][i] = smithy;
                }
        }

	cardEffect(adventurer, choice1, choice2, choice3, &test, handpos, bonus);	
	// count treasure in hand
	int treasureFound = 0; 
        for (i = 0; i < test.handCount[player]; i++){
                cardDrawn = test.hand[player][i];
                if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
                        treasureFound++;
                }
        }
	
        printf("%s", "Testing Adventurer card with deck full of treasure: ");
        if(myAssert(treasureFound, 2) == 0){
                printf("%s%d\n","FAIL: Improper number of treasure cards added to deck. Expected: 2 Actual: ", treasureFound);
        }
        else{
                printf("%s\n", "PASS: No treasure cards added to deck and infinite loop avoided.");
        }



	/***	TEST2 - TEST ADVENTURER CARD WITH 0 TREASURE CARDS IN DECK	***/
	int foundTreasure = 0;
	for (i = 0; i < test.deckCount[player]; i++){
		cardDrawn = test.deck[player][i];
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
			test.deck[player][i] = 0;
		}
	}

	// remove all treasure from hand to test for occurance after running card
	for (i = 0; i < test.handCount[player]; i++){
                cardDrawn = test.hand[player][i];
                if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
                        test.hand[player][i] = 0;
                }
        }
	
	// run the card
	cardEffect(adventurer, choice1, choice2, choice3, &test, handpos, bonus);
	
	// check for addition of treasure
        for (i = 0; i < test.handCount[player]; i++){
                cardDrawn = test.hand[player][i];
                if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
                        foundTreasure = 1;
                }
        }

	// output
        printf("%s", "Testing Adventurer card with all Treasure cards removed from deck: ");
        if(myAssert(foundTreasure, 0) == 0){
                printf("%s\n","FAIL: Treasure card added to hand with none available.");
        }
        else{
                printf("%s\n", "PASS: No treasure cards added to deck and infinite loop avoided.");
        }
	
	/***	TEST 3 - TEST ADVENTURER CARD WITH 1 TREASURE CARD IN DECK	***/
	// clear out hand in case first test failed and added treasure to hand
        for (i = 0; i < test.handCount[player]; i++){
                cardDrawn = test.hand[player][i];
                if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
                        test.hand[player][i] = 0;
                }
        }
	
	
	cardEffect(adventurer, choice1, choice2, choice3, &test, handpos, bonus);
	// test for 1 treasure added
	treasureFound = 0;
        for (i = 0; i < test.handCount[player]; i++){
                cardDrawn = test.hand[player][i];
                if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
                        treasureFound++;
			printf("found one");
                }
        }
	
	// output
        printf("%s", "Testing Adventurer card with only one treasure card in deck: ");
        if(myAssert(treasureFound, 0) == 1){
                printf("%s\n","FAIL: No treasure cards added to deck.");
        }
	else if(myAssert(treasureFound, 1) == 0){
		printf("%s\n", "FAIL: Too many treasure cards added to deck.");
	}
        else{
                printf("%s\n", "PASS: One treasure added to hand.");
        }
}

int main(){
        testAdventurer();
        return 0;
}
