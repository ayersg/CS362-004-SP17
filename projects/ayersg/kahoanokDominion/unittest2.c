/**********************************************************
*
*	unittest2.c
*	
*	CS 362 - Software Engineering II
*	Gillian Ayers
*
*	Test for updateCoins function in dominion.c
*	Function:
*			int updateCoins(int player, struct gameState *state, int bonus){
*			  int i;
*			  state->coins = 0;
*
*			  //add coins for each Treasure card in player's hand
*				for (i = 0; i < state->handCount[player]; i++){
*					if (state->hand[player][i] == copper){
*							state->coins += 1;
*					}
*					else if (state->hand[player][i] == silver){
*							state->coins += 2;
*					}
*					else if (state->hand[player][i] == gold){
*							state->coins += 3;
*					}	
*				}	
*			  //add bonus
*			  state->coins += bonus;
*			  return 0;
*			}
*				
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

#define TESTUNIT "updateCoins"

int callupdateCoins(int p, struct gameState *G, int bonus, int handCount) {
    int flag = 0;	
    int r = updateCoins(p, G, bonus);

    if(r != 0){
    	printf("TEST FAIL: Problem with function call to updateCoints.\n");
    	flag = 1;
    }

    if(*G->hand[p] == copper)
    {
    	printf("Coins = %d, Expected Coins = %d\n", G->coins, handCount * 1 + bonus);
    	if(G->coins != handCount * 1 + bonus){
    		printf("TEST FAIL: Copper\n");
    		flag = 1;
    	}
    } else if(*G->hand[p] == silver) {
    	printf("Coins = %d; Expected Coins= %d\n", G->coins, handCount * 2 + bonus);
		if(G->coins != handCount * 2 + bonus){
			printf("TEST FAIL: Silver\n");
			flag = 1;
		}
    } else { //gold
		printf("Coins = %d; Expected Coins = %d\n", G->coins, handCount * 3 + bonus);
		if(G->coins != handCount * 3 + bonus){
			printf("TEST FAIL: Gold\n");
			flag = 1;
		}
    }

	return flag;
}

int main() {

	printf("\n\n----------------- UNIT TEST: %s function ----------------\n\n", TESTUNIT);
	
    int handCount;
    int bonus;
	int seed = 1000;
    int numPlayer = MAX_PLAYERS;
    int maxBonus = 10;
    int maxHandCount = 5;
    int flag = 0;
	
	struct gameState G;

	int arrayOfCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    for (int i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

	for (int j = 0; j < numPlayer; j++)
	{
       for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
                printf("Testing player #%d with %d treasure card(s) and %d bonus.\n", j, handCount, bonus);
               
                memset(&G, 23, sizeof(struct gameState));
                initializeGame(numPlayer, arrayOfCards, seed, &G);

                G.handCount[j] = handCount;                 // set the number of cards on hand

                memcpy(G.hand[j], coppers, sizeof(int) * handCount);
                flag = callupdateCoins(j, &G, bonus, handCount);

                memcpy(G.hand[j], silvers, sizeof(int) * handCount);
                flag = callupdateCoins(j, &G, bonus, handCount);

                memcpy(G.hand[j], golds, sizeof(int) * handCount);
                flag = callupdateCoins(j, &G, bonus, handCount);

            }
        }
    }

	if (flag == 1) {
		printf("\nUNIT TEST %s FAILED.\n\n", TESTUNIT);
	} else {
		printf("\nUNIT TEST %s PASSED.\n\n", TESTUNIT);
	}

}