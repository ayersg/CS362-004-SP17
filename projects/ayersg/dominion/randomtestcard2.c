#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_CARD "Sea Hag"

//Card functionality: Each other player discards the top card of his deck, then gains a Curse card.

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

	//BEGIN GAME - 4 Players (Sea hag is no fun with two)
	//int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state)
	initializeGame(4, k, atoi(args[1]), &game);
	srand(atoi(args[1]));

	printf("\nSelected %d seconds to run randomtestcard1\n", timeRemaining);
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
		gainCard(sea_hag, &g, 2, 0);

		//int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
		//playCard calls cardEffect
		//int numHandCards(struct gameState *state) { return state->handCount[ whoseTurn(state) ];}
		if (playCard(numHandCards(&g)-1, 0, 0, 0, &g) < 0){
				printf("Failed at function playCard.\n");
				printf("numHandCards(&g)-1 = %d\n", (numHandCards(&g)-1));
		}

		//Cycle through all 4 players
		for(int j=0; j<4; j++){
			//Check here for curses and discarded cards in players' hands
		}

		endTurn(&g);

		}

	printf("\n****TESTING COMPLETED****\n\n");

	return 0;

}