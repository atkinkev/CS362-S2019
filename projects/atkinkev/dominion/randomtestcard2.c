/**********************************************************************************************************
 * Kevin Atkins
 * 5/6/2019
 * randomtestcard2.c
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
#include "limits.h"



int myAssert(int val1, int val2){
        if (val1 != val2){
                return 0;
        }
        else{
                return 1;
        }
}

void randomSteward(){
        struct gameState test;
        struct gameState original;
        int player = 0;
        int choice1 = 0;
        int choice2 = 0;
        int choice3 = 0;
        int handpos = 0;
        int deckSize = 0;
        int handSize = 0;
        int bonus[] = {};
        int i,j= 0;
        int hCountFails = 0;
	int coinCountFails = 0;
	int discardCountFails = 0;
        int k[10] = {adventurer, steward, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};


        printf("\n*****************************************************************************\n");
        printf("%s\n", "*************************** BEGIN STEWARD TEST ***************************");
        printf("*****************************************************************************\n");

        srand(time(0));

        for (i = 0; i < 100000; i++){
                initializeGame(2, k, 30, &test);
                player = whoseTurn(&test);
		
		// setup choice and coin params
		choice1 = rand() % 3  + 1;
		choice2 = rand() % 28;
		choice3 = rand() % 28;
		test.coins = rand() % RAND_MAX;

		// setup deck and hand sizes
                deckSize = rand() % MAX_DECK + 1;
                handSize = rand() % deckSize + 1;
                test.deckCount[player] = deckSize - handSize;
                test.handCount[player] = handSize;
			
                for(j = 0; j < test.deckCount[player]; j++){
                	test.deck[player][j] = rand() % 28;
                }

                for(j = 0; j < test.handCount[player]; j++){
                	test.hand[player][j] = rand() % 28;
                }
		test.hand[player][test.handCount[player] - 1] = steward;
		
                handpos = test.hand[player][test.handCount[player] - 1];
                memcpy(&original, &test, sizeof(struct gameState));

		cardEffect(steward, choice1, choice2, choice3, &test, handpos, bonus);

		if (choice1 == 1){
			if (myAssert(test.handCount[player], original.handCount[player] + 1) == 0 && test.deckCount[player] > 2){
				if (hCountFails < 10){
					printf("%s%d%s%d\n", "(** CHOICE1 = 1 ** FAIL -- Expected post-card hand count: ", original.handCount[player] + 1, " Actual: ", test.handCount[player]);
				}
				hCountFails++;			
				if (hCountFails == 10){
					printf("More than 10 'choice1 = 1' fails recorded.\n");
				}
			}	 	
		}
		else if (choice1 == 2){
                        if (myAssert(test.coins, original.coins + 2 ) == 0){
				if (coinCountFails < 10){
                                	printf("%s%d%s%d\n", "** CHOICE1 = 2 ** FAIL -- Expected coins: ", original.coins + 2, " Actual: ", test.coins);
                                }
				coinCountFails++;
				if (coinCountFails == 10){
					printf("More than 10 'choice1 = 2' fails recorded.\n");
				}
			}
		}
		else if (choice1 == 3){
			if (myAssert(test.handCount[player], original.handCount[player] - 3) == 0){
				if(discardCountFails < 10){
					printf("%s%d%s%d\n", "** CHOICE1 = 3 ** FAIL -- Expected post-card hand count: ", original.handCount[player] - 3, " Actual: ", test.handCount[player]);
				}
				discardCountFails++;
			}
			if (discardCountFails == 10){
				printf("More than 10 'choice1 = 3' fails recorded.\n"); 
			}
		}
		
	}
        printf("\n**** END OF TEST SUMMARY ****\n");
	printf("CHOICE1 = 1: Test post card hand count incrementing properly: ");
	if (hCountFails > 0){
		printf("FAIL\n");
	}
	else {
		printf("PASS\n");
	}
        printf("CHOICE1 = 2: Test post card coins incrementing properly: ");
        if (coinCountFails > 0){
                printf("%s%d\n","FAILS: ", coinCountFails);
        }
        else {
       	     printf("PASS\n");
        }
	printf("CHOICE1 = 3: Test post card hand count decrementing properly: ");
	if (discardCountFails > 0){
		printf("FAIL\n");
	}
	else {
		printf("PASS\n");
	}
}

int main(){
	randomSteward();
	return 0;
}
