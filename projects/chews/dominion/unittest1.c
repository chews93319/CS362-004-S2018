
/* 
 * File:   unittest1.c
 * Author: Sam Chew
 * ONID: chews 933191613
 *
 * Created on April 24, 2018, 12:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"


//set NOISY1 to 0 to remove printfs from output
#define NOISY1 1


/*
 * Unit Test for Function: playCard
 */
int main(int argc, char** argv) {
    
#if (NOISY1 == 1)
    printf("*** This was Unit Test 1 ***\n");
#endif
    
    int i, p;
    int r;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int deckqty, handqty;
    char name[MAX_STRING_LENGTH];
    
    
    // clear the game state memory space
    memset(&G, 23, sizeof(struct gameState));
    
    // initialize a new game
    r = initializeGame(numPlayer, k, seed, &G);
    
#if (NOISY1 == 1)
    if (r >= 0) printf("Game Initialized\n");
    
    for (p=0;p<numPlayer;p++){
        printf("player%d Deck:\n",p);
        deckqty = G.deckCount[p];
        for (i=0;i<deckqty;i++){
            cardNumToName(G.deck[p][i], name);
            printf("%s, ",name);
        }
        printf("\nplayer%d Hand:\n",p);
        handqty = G.handCount[p];
        for (i=0;i<handqty;i++){
            cardNumToName(G.deck[p][i], name);
            printf("%s, ",name);
        }
        printf("\n");
    }
    
    for (i = 0; i < treasure_map+1; i++){
        if (G.supplyCount[i] > -1){
            cardNumToName(i, name);
            printf("%s: %d\n",name,G.supplyCount[i]);
        }
    }
#endif
    
    
    return (EXIT_SUCCESS);
}

