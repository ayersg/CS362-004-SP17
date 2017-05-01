/**********************************************************
*
*	unittest1.c
*	
*	CS 362 - Software Engineering II
*	Gillian Ayers
*
*	Test for whoseTurn function in dominion.c
*	Function:
*		int whoseTurn(struct gameState *state) {
*  				return state->whoseTurn;
*		}				
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

#define TESTUNIT "whoseTurn"

int main() {

	printf("\n\n----------------- UNIT TEST: %s function ----------------\n\n", TESTUNIT);

	struct gameState G;
	int arrayOfCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int numPlayers = MAX_PLAYERS;
	int seed = 1000;
	int s = 0;
	int t = 0;
	int flag = 0;

	initializeGame(numPlayers, arrayOfCards, seed, &G);

	for(int i=0; i < 200; i++){
		G.whoseTurn = s; 
		t = whoseTurn(&G);

		if(s != t){
			printf("TEST FAIL: Test #%d, whoseTurn attribute does not equal whoseTurn function call results.\n", i);
			flag = 1;
		}

		s++;
	}

	if (flag == 1) {
		printf("\nUNIT TEST %s FAILED.\n\n", TESTUNIT);
	} else {
		printf("\nUNIT TEST %s PASSED.\n\n", TESTUNIT);
	}

}