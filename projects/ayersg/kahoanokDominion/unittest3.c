/**********************************************************
*
*	unittest3.c
*	
*	CS 362 - Software Engineering II
*	Gillian Ayers
*
*	Test for isGameOver function in dominion.c
*	Function:
*int isGameOver(struct gameState *state) {
*
*	//if stack of Province cards is empty, the game ends
*	if (state->supplyCount[province] == 0){
*		return 1;
*	}
*
*	//if three supply pile are at 0, the game ends
*	int j = 0;
*	for (int i = 0; i < 25; i++){
*		if (state->supplyCount[i] == 0){
*			j++;
*		}
*	}
*	if ( j >= 3){
*		return 1;
*	}
*
*	return 0;
*}		
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

#define TESTUNIT "isGameOver"

int main() {

	printf("\n\n----------------- UNIT TEST: %s function ----------------\n\n", TESTUNIT);

	printf("\nTEST 1: Game over with 0 Province cards\n");

	int arrayOfCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	struct gameState G;

	int numPlayers = MAX_PLAYERS;
	int seed = 1000;
	int flag = 0;

	initializeGame(numPlayers, arrayOfCards, seed, &G);

	//Set the number of Province cards to 0 to end the game
	G.supplyCount[province] = 0;
	int result = isGameOver(&G);

	if(result == 0){
		printf("TEST FAIL: Game is not over with 0 Province cards left.\n");
		flag = 1;
	}

	printf("\nTEST 2: Game over with three empty supply piles\n");

	struct gameState testG;
	initializeGame(2, arrayOfCards, seed, &testG);

	//Set three supply piles to zero
	testG.supplyCount[1] = 0;
	testG.supplyCount[3] = 0;
	testG.supplyCount[8] = 0;

	int result2 = isGameOver(&testG);

	if(result2 == 0){
		printf("TEST FAIL: Game is not over with three emply supply piles.\n");
		flag = 1;
	}

	if (flag == 1) {
		printf("\nUNIT TEST %s FAILED.\n\n", TESTUNIT);
	} else {
		printf("\nUNIT TEST %s PASSED.\n\n", TESTUNIT);
	}

}