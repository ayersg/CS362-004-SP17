/**********************************************************
*
*	cardtest3.c
*	
*	CS 362 - Software Engineering II
*	Gillian Ayers
*
*	Test for Adventurer card in Dominion
*	Card Description:
*		"Reveal cards from your deck until you reveal 2 Treasure cards. Put those Treasure cards into your hand and discard other revealed cards."
*
*	References:
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

#define TESTCARD "Adventurer"

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
    int numTreasure = 0;
    int numTreasure2 = 0;

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
		printf("handCount: %d  (There should intially be 5)\n", G.handCount[i]);
		printf("discardCount: %d\n\n", G.discardCount[i]);
	}

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    printf("\nTEST 1: +2 Treasure cards\n");
    printf("Player draws cards from their deck until 2 Treasure cards are revealed.\n");

	memcpy(&testG, &G, sizeof(struct gameState));

    for(int i =0; i < G.handCount[currPlayer]; i++){
        if(G.hand[currPlayer][i] == copper || G.hand[currPlayer][i] == silver || G.hand[currPlayer][i] == gold){
        numTreasure++;
        }
    }
    printf("Original Treasure count in hand for player %d: %d\n", currPlayer+1, numTreasure);

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    for(int i =0; i < testG.handCount[currPlayer]; i++){
        if(testG.hand[currPlayer][i] == copper || testG.hand[currPlayer][i] == silver || testG.hand[currPlayer][i] == gold){
            numTreasure2++;
        }
    }

    printf("Treasure count in hand for player %d AFTER playing Adventurer: %d\n", currPlayer+1, numTreasure2);

    if(numTreasure2 != numTreasure + 2){
        printf("TEST FAIL: Treasure card count did not increment correctly.  Must increment by 2.\n");
        flag = 1;
    }

    if (flag == 1) {
        printf("\nTEST 1 FAILED.\n\n");
    } else {
        printf("\nTEST 1 PASSED.\n\n");
    }

    printf("\nTEST 2: Discard revealed cards.\n");
    printf("Player must discard all the non-Treasure cards they revealed.\n");

    flag=0;
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    if((testG.deckCount[currPlayer] + testG.discardCount[currPlayer]) != (G.deckCount[currPlayer] + G.discardCount[currPlayer] - 2))
    {
        printf("TEST FAIL: Expected Value: %d  Actual Value: %d\n", testG.deckCount[currPlayer] + testG.discardCount[currPlayer], 
        G.deckCount[currPlayer] + G.discardCount[currPlayer] - 2);
        flag=1;
    }

    if (flag == 1) {
        printf("\nTEST 2 FAILED.\n\n");
    } else {
        printf("\nTEST 2 PASSED.\n\n");
    }

    printf("\n\n >>>>> TEST COMPLETED <<<<<\n");
    printf(" >>>>> CARD %s <<<<<\n\n", TESTCARD);




}