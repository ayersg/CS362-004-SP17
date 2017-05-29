/**********************************************************
*
*	cardtest1.c
*	
*	CS 362 - Software Engineering II
*	Gillian Ayers
*
*	Test for Steward card in Dominion
*	Card Description:
*		"Choose one: +2 Cards; or +2 Coins; or trash 2 cards from your hand."
*		"If you pick "trash 2 cards from your hand" and only have one card in hand, you trash that card; if you choose that option and have 2 or more cards in hand, you have to trash 2."
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

#define TESTCARD "Steward"

int main() {

    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int handpos = 0;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int currPlayer = 0;
    int flag = 0;

    // For a two-player game
    int numPlayers = 2;

	struct gameState G;
	struct gameState testG;

	int arrayOfCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// Initialize a game
	initializeGame(numPlayers, arrayOfCards, seed, &G);

	printf("\n----------------- Verifying Initial Game State ----------------\n");

	printf("Two-player game begins with an expected 8 Victory Point cards.\n");
    printf("Actual # of Estate cards: %d\n", G.supplyCount[1]);
    printf("Actual # of Duchy cards: %d\n", G.supplyCount[2]);
    printf("Actual # of Province cards: %d\n\n", G.supplyCount[3]);
    printf("Checking player hands....\n");
    printf("Player Count: %d\n\n", numPlayers);
    for(int i=0; i < numPlayers; i++){
    	int num = i+1;
		printf("Player #%d\n", num);
		printf("coins: %d\n", G.coins);
		printf("deckCount: %d\n", G.deckCount[i]);
		printf("handCount: %d\n", G.handCount[i]);
		printf("discardCount: %d\n\n", G.discardCount[i]);
	}

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	printf("\nTEST 1: choice1 = 1 = +2 cards\n");
	printf("Test case in which player has selected to draw two cards.\n");

	// Copy the game to a test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 1;
	newCards = 2;
	xtraCoins = 0;

	// Use test game state testG to test effect of card
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	for(int i = 0; i < numPlayers; i++){
		int num = i+1;
		printf("\nPlayer #%d\n", num);
		printf("Test hand count = %d, Expected hand count = %d\n", testG.handCount[i], G.handCount[i] + newCards - discarded);
		printf("Test deck count = %d, Expected deck count = %d\n", testG.deckCount[i], G.deckCount[i] - newCards + shuffledCards);
		printf("Test coins = %d, Expected coins = %d\n", testG.coins, G.coins + xtraCoins);
		printf("Test discard count = %d, Expected discard count = %d\n", testG.discardCount[i], G.discardCount[i]);
		
		if(i == currPlayer){
			if(testG.handCount[currPlayer] != G.handCount[currPlayer] + newCards){
				printf("TEST FAIL: Hand count didn't increment properly. Must increase by 2.\n");
				flag = 1;
			}

			if(testG.deckCount[currPlayer] != G.deckCount[currPlayer] - newCards + shuffledCards){
				printf("TEST FAIL: Deck count didn't decrement properly.\n");
				flag = 1;
			}

			if(testG.discardCount[currPlayer] != G.discardCount[currPlayer]){
				printf("TEST FAIL: Discard counts don't match.\n");
				flag = 1;
			}
		}else{
			printf("((Not current player; there should be no change.))\n");			
			if(testG.handCount[i] != G.handCount[i]){
			printf("TEST FAIL: Hand counts don't match.\n");
			flag = 1;
			}

			if(testG.deckCount[i] != G.deckCount[i]){
			printf("TEST FAIL: Deck counts don't match.\n");
			flag = 1;
			}

			if(testG.discardCount[i] != G.discardCount[i]){
			printf("TEST FAIL: Discard counts don't match.\n");
			flag = 1;
			}
		}

		if(testG.coins != G.coins + xtraCoins){
			printf("TEST FAIL: Coins don't match for player %d\n", i);
			flag = 1;
		}
	}

	if(flag == 1){
		printf("\nTEST 1 FAILED.\n\n");
	}else{
		printf("\nTEST 1 PASSED.\n\n");
	}

	printf("\nTEST 2: choice1 = 2 = +2 coins\n");
	printf("Test case in which player has selected +2 coins.\n");

	// Copy the game to a test game state
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 2;
	newCards = 0;
	xtraCoins = 2;
	flag = 0;

	// Use test game state testG to test effect of card
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	for(int i = 0; i < numPlayers; i++){
		int num = i+1;
		printf("\nPlayer #%d\n", num);
		printf("Test hand count = %d, Expected hand count = %d\n", testG.handCount[i], G.handCount[i] + newCards - discarded);
		printf("Test deck count = %d, Expected deck count = %d\n", testG.deckCount[i], G.deckCount[i] - newCards + shuffledCards);
		printf("Test coins = %d, Expected coins = %d\n", testG.coins, G.coins + xtraCoins);
		printf("Test discard count = %d, Expected discard count = %d\n", testG.discardCount[i], G.discardCount[i]);
		
		if(i == currPlayer){
			if(testG.handCount[currPlayer] != G.handCount[currPlayer] + newCards - discarded){
				printf("TEST FAIL: Hand count didn't increment properly.\n");
				flag = 1;
			}

			if(testG.deckCount[currPlayer] != G.deckCount[currPlayer] - newCards + shuffledCards){
				printf("TEST FAIL: Deck count didn't decrement properly.\n");
				flag = 1;
			}

			if(testG.discardCount[currPlayer] != G.discardCount[currPlayer]){
				printf("TEST FAIL: Discard counts don't match.\n");
				flag = 1;
			}
		}else{
			printf("((Not current player; there should be no change.))\n");
			if(testG.handCount[i] != G.handCount[i]){
			printf("TEST FAIL: Hand counts don't match.\n");
			flag = 1;
			}

			if(testG.deckCount[i] != G.deckCount[i]){
			printf("TEST FAIL: Deck counts don't match.\n");
			flag = 1;
			}

			if(testG.discardCount[i] != G.discardCount[i]){
			printf("TEST FAIL: Discard counts don't match.\n");
			flag = 1;
			}
		}

		if(testG.coins != G.coins + xtraCoins){
			printf("TEST FAIL: Coins don't match for player %d\n", i);
			flag = 1;
		}
	}

	if(flag == 1){
		printf("\nTEST 2 FAILED.\n\n");
	}else{
		printf("\nTEST 2 PASSED.\n\n");
	}

	printf("TEST 3: choice1 = 3 = trash two cards\n");
	printf("Test case in which player has selected to trash two cards.\n");
	choice1 = 3;
	flag = 0;

	// cycle through each eligible combination of 2 cards to trash
	// primarily from the function provided in class
	for (int i=1; i<G.handCount[currPlayer]; i++) {
		for (int j=i+1; j<G.handCount[currPlayer]; j++) {

			G.hand[currPlayer][0] = steward;
			G.hand[currPlayer][1] = copper;
			G.hand[currPlayer][2] = duchy;
			G.hand[currPlayer][3] = estate;
			G.hand[currPlayer][4] = feast;

			memcpy(&testG, &G, sizeof(struct gameState));

			printf("\nStarting cards: ");
			for (int m=0; m<testG.handCount[currPlayer]; m++) {
				printf("(%d)", testG.hand[currPlayer][m]);
			}
			printf("; ");

			choice2 = j;
			choice3 = i;

			remove1 = testG.hand[currPlayer][i];
			remove2 = testG.hand[currPlayer][j];

			cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

			printf("removed cards: (%d)(%d); ", remove1, remove2);

			printf("ending cards: ");
			for (int m=0; m<testG.handCount[currPlayer]; m++) {
				printf("(%d)", testG.hand[currPlayer][m]);
			}

			printf(", expected to be removed: ");
			for (int m=1; m<G.handCount[currPlayer]; m++) {
				if (G.hand[currPlayer][m] != G.hand[currPlayer][i] && G.hand[currPlayer][m] != G.hand[currPlayer][j]) {
					printf("(%d)", G.hand[currPlayer][m]);
				}
			}
			printf("\n");

			// tests for the appropriate number of remaining cards
			newCards = 0;
			xtraCoins = 0;
			discarded = 3;

			if (i==1 && j==2) {
				printf("hand count = %d, expected = %d\n", testG.handCount[currPlayer], G.handCount[currPlayer] + newCards - discarded);
				printf("deck count = %d, expected = %d\n", testG.deckCount[currPlayer], G.deckCount[currPlayer] - newCards + shuffledCards);
			}
		}

	}

	printf("\n\n >>>>> TEST COMPLETED <<<<<\n");
	printf(" >>>>> CARD %s <<<<<\n\n", TESTCARD);

	return 0;
}
