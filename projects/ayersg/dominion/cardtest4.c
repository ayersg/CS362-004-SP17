/**********************************************************
*
*	cardtest4.c
*	
*	CS 362 - Software Engineering II
*	Gillian Ayers
*
*	Test for Village card in Dominion
*	Card Description:
*		"+1 Card, +2 Actions"
*
*	References:
*		Based off of the example test from class in "cardtest4.c"
*		Card information taken from Dominion Strategy wiki	
*
**********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTCARD "Village"

int main() {

    int newCards = 0;
    //int discarded = 0;
    //int xtraCoins = 0;
    //int shuffledCards = 0;
    int handpos = 0;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int currPlayer = 0;
    int flag = 0;

    int numPlayers = MAX_PLAYERS;	//defined in dominion.h

	struct gameState G;
	struct gameState testG;

	int arrayOfCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

			// Initialize a game
	initializeGame(numPlayers, arrayOfCards, seed, &G);

	printf("\n----------------- Verifying Initial Game State ----------------\n");

	printf("Two-player game begins with an expected 8 Victory Point cards, otherwise there are 12 VP cards.\n");
    printf("Actual # of Estate cards: %d\n", G.supplyCount[1]);
    printf("Actual # of Duchy cards: %d\n", G.supplyCount[2]);
    printf("Actual # of Province cards: %d\n\n", G.supplyCount[3]);

    printf("Checking player hands....\n");
    printf("Player Count: %d\n", numPlayers);
    for(int i=0; i < numPlayers; i++){
    	int num = i+1;
		printf("Player #%d\n", num);
		printf("coins: %d\n", G.coins);
		printf("deckCount: %d\n", G.deckCount[i]);
		printf("handCount: %d\n", G.handCount[i]);
		printf("discardCount: %d\n\n", G.discardCount[i]);
	}

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	printf("\nTEST 1: +1 cards\n");
	printf("Player gets to draw 1 cards.\n");

	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 1;

	for(int i=0; i < MAX_PLAYERS; i++) {
		int num = i+1;
		printf("\nPlayer %d\n", num);
		printf("Test Hand Count after playing Village = %d, Orignal Hand Count = %d\n", testG.handCount[i], G.handCount[i]);
		printf("Test Deck Count after playing Village = %d, Original Deck Count = %d\n", testG.deckCount[i], G.deckCount[i]);
		printf("Test Discard Count after playing Village= %d, Original Discard Count = %d\n", testG.discardCount[i], G.discardCount[i]);
		
		if(i == currPlayer){
			if(testG.handCount[i] != G.handCount[i] + newCards){
				printf("TEST FAIL: Hand counts didn't increment properly. Must increment by 1.\n");
				flag = 1;
			}
			if(testG.deckCount[i] != G.deckCount[i] - newCards){
				printf("TEST FAIL: Deck counts didn't decrement properly. 1 card drawn from deck, must decrement by 1.\n");
				flag = 1;
      		}
			if(testG.discardCount[i] != G.discardCount[i]){
				printf("TEST FAIL: Discard counts don't math pre-function call and post-function call.\n");
				flag = 1;
      		}
		}else{
			printf("((Not current player; there should be no change.))\n");
			if(testG.handCount[i] != G.handCount[i]){
				printf("TEST FAIL: Hand counts for non-current player don't match.\n");
				flag = 1;
			}
      
			if(testG.deckCount[i] != G.deckCount[i]){
				printf("TEST FAIL: Deck counts for non-current player don't match.\n");
				flag = 1;
			}
			if(testG.discardCount[i] != G.discardCount[i]){
				printf("TEST FAIL: Discard counts for non-current player don't match.\n");
				flag = 1;
			}

    }
  }

	if (flag == 1) {
		printf("\nTEST 1 FAILED.\n\n");
	} else {
		printf("\nTEST 1 PASSED.\n\n");
	}

	printf("\nTEST 2: +2 Actions\n");
	printf("Player gets to draw 1 cards.\n");
	flag = 0;

	memcpy(&testG, &G, sizeof(struct gameState));
	printf("Number of actions available BEFORE playing Village card: %d\n", G.numActions);
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Number of actions available AFTER playing Village card: %d\n", testG.numActions);

	if(testG.numActions != G.numActions + 2){
		printf("TEST FAIL: Actions not increased by 2.\n");
		flag = 1;
	}

	if (flag == 1) {
		printf("\nTEST 2 FAILED.\n\n");
	} else {
		printf("\nTEST 2 PASSED.\n\n");
	}


	printf("\n\n >>>>> TEST COMPLETED <<<<<\n");
	printf(" >>>>> CARD %s <<<<<\n\n", TESTCARD);


}