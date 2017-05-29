/**********************************************************
*
*	unittest4.c
*	
*	CS 362 - Software Engineering II
*	Gillian Ayers
*
*	Test for getCost function in dominion.c
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

#define TESTUNIT "getCost"

int main() {

	printf("\n\n----------------- UNIT TEST: %s function ----------------\n\n", TESTUNIT);

	int wrong;
	int c = getCost(adventurer);
	int m = getCost(minion);
	int s = getCost(smithy);
	int x = getCost(wrong);
	int flag = 0;

	if(c != 6){
		printf("TEST FAIL: Wrong cost for adventurer.\n");
		flag = 1;
	}
	if(m != 5){
		printf("TEST FAIL: Wrong cost for minion.\n");
		flag =1;
	}
	if(s != 4){
		printf("TEST FAIL: Wrong cost for smithy.\n");
		flag = 1;
	}
	if(x != -1){
		printf("TEST FAIL: Must return -1 for wrong input.\n");
		flag =1;
	}

	if (flag == 1) {
		printf("\nUNIT TEST %s FAILED.\n\n", TESTUNIT);
	} else {
		printf("\nUNIT TEST %s PASSED.\n\n", TESTUNIT);
	}

}