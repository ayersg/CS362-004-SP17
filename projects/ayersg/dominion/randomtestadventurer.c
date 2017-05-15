#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_CARD "Adventurer"

//Card functionality: Reveal cards from your deck until you reveal 2 Treasure cards.

int main(int argc, char* args[])
{
	if(argc != 3)
	{
		printf("Incorrect number of parameters.\n");
		return -1;
	}

	printf("\n\nRANDOM TESTING FOR %s CARD\n\n", TEST_CARD);

	int k[10] = {adventurer, gardens, embargo, village, minion, ambassador, cutpurse, sea_hag, tribute, smithy};
	struct gameState g, game;
	int r;
	int timeRemaining = atoi(args[2]);
	int numHand, numDeck; 

	//BEGIN GAME
	//int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state)
	initializeGame(2, k, atoi(args[1]), &game);
	srand(atoi(args[1]));

	printf("\nSelected %d seconds to run randomtestadventurer\n", timeRemaining);
	clock_t start = clock();

	while(1)
	{
		//Tracks how much time has passed for each loop
		clock_t totalTime = (clock() - start) / CLOCKS_PER_SEC;

		//If time runs out
		if(totalTime >= timeRemaining)
			break;

		memcpy(&g, &game, sizeof(struct gameState));
		numHand = rand() % 10;
		numDeck = rand() % 20;
		g.deckCount[0] = numDeck;
		g.handCount[0] = numHand;

		//Randomize deck 
		for(int i = 0; i < numDeck; ++i)
		{
			g.deck[0][i] = rand() % (treasure_map+1);	//treasure_map is the last card in the stack of cards
		}

		//Randomize hand
		for(int i = 0; i < numHand; ++i)
		{
			g.hand[0][i] = rand() % (treasure_map+1);
		}

		//int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
		gainCard(adventurer, &g, 2, 0);


		int originalTotal = fullDeckCount(0, adventurer, &g);

		//int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
		//playCard calls cardEffect
		//
		if (playCard(numHandCards(&g)-1, 0, 0, 0, &g) < 0){
				printf("Failed at function playCard.\n");
				printf("numHandCards(&g)-1 = %d", numHandCards(&g)-1);
				return -1;
		}

		int diff = numHandCards(&g)-numHand;
		if(diff < 0 || diff > 2){
			printf("Difference between old hand count and new hand count is wrong.\n");
			printf("Should only gain two treasure cards, one treasure card, or none.\n");
		}

		for(int i = 0; i < diff; ++i){
			int card = (handCard(numHandCards(&g)-1-i, &g));
			if (card > gold || card < copper){
				printf("Unexpected non-Treasure card.\n");
			}
		}
		endTurn(&g);

		//Check to see if the total card count after all of this is still correct
		if(originalTotal != fullDeckCount(0, adventurer, &g)){
			printf("Either cards have been lost or the wrong cards have been gained!\n");
			printf("Original Total: %d\n", originalTotal);
			printf("fullDeckCount: %d\n", fullDeckCount(0, adventurer, &g));
		}
	}

	printf("\n****TESTING COMPLETED****\n\n");

	return 0;
}