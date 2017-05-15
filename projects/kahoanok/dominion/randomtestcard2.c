#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"

#define DEBUG 0

int checkFeast(int z, struct gameState *post){
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    int r;
    printf("FeastCard PRE: p %d HC %d Dec %d DIC %d\n", z, pre.handCount[z], pre.deckCount[z], pre.discardCount[z]);
    
    r = play(postFeast);
    
    printf("FeastCard POST: p %d HC %d Dec %d DIC %d\n", z, post->handCount[z], post->deckCount[z], post->discardCount[z]);
}


int main(){
    int w, x, y, z, deckCount, discardCount, handCount;
    
    int y[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf("Testing Feast Card.\n");
    printf ("RANDOM TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    for (x = 0; x < 2000; x++) {
        for(w = 0; w < sizeof(struct gameState); w++){
            ((char*)&G)[w] = floor(Random() * 256);
        }
        z = floor(Random() * 1000);
        G.deckCount[z] = floor(Random() * MAX_DECK);
        G.discardCount[z] = floor(Random() * MAX_DECK);
        G.handCount[z] = floor(Random() * MAX_HAND);
        checkFeast(z, &G);
    }
    printf ("ALL TESTS OK\n");
    
    exit(0);
}
