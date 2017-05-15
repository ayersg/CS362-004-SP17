#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"

#define DEBUG 0


int checkCouncilRoom(int p, struct gameState *post){
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    int r;
    printf("CouncilRoomCard PRE: p %d HC %d Dec %d DIC %d\n", p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
    
    r = playCouncil_Room(post, p);
    
    printf("CouncilRoomCard POST: p %d HC %d Dec %d DIC %d\n", p, post->handCount[p], post->deckCount[p], post->discardCount[p]);
}

int main(){
    int i, n, r, p, deckCount, discardCount, handCount;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf("Testing Adventure Card.\n");
    printf ("RANDOM TESTS.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    for (n = 0; n < 2000; n++) {
        for(i = 0; i < sizeof(struct gameState); i++){
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * 1000);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        checkCouncilRoom(p, &G);
    }
    printf("ALL TESTS OK\n");
    
    exit(0);
}
