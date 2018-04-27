
/* 
 * File:   unittest2.c
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


//set NOISY2 to 0 to remove printfs from output
#define NOISY2 1

//function prototypes
int asserttrue(int lefty, int righty);
void printSupplySet(struct gameState* g);
void printCardSet(int player, struct gameState* g);



/*
 * Unit Test for Function: endTurn
 */
int main(int argc, char** argv) {
    
//#if (NOISY2 == 1)
    printf("*** Start of Unit Test 2 ***\n");
//#endif
    
    int i, p;
    int r;
    int seed = 1000;
    int numPlayer = 2;
    int who;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState G;
    
    int failqty = 0;
    
    // clear the game state memory space
    memset(&G, 23, sizeof(struct gameState));
    
    // initialize a new game
    r = initializeGame(numPlayer, k, seed, &G);
    
#if (NOISY2 == 1)
    if (r >= 0) printf("Game Initialized\n\n");
    
    printSupplySet(&G);
    
    printf("\n");
    printf("Whose Turn: %d\n", G.whoseTurn);
    printf("Coin Qty: %d\n", G.coins);
    
    for (p=0;p<numPlayer;p++){
        printCardSet(p, &G);
    }
#endif
    
    // Change from player0 to player1
    endTurn(&G);
    
    failqty += asserttrue(G.handCount[0],0);
    failqty += asserttrue(G.discardCount[0],5);
    failqty += asserttrue(G.whoseTurn,1);
    //count and validate coins
    
    // Change from player1 to player0
    endTurn(&G);
    
    failqty += asserttrue(G.handCount[1],0);
    failqty += asserttrue(G.discardCount[1],5);
    failqty += asserttrue(G.whoseTurn,0);
    //count and validate coins
    
    
    
/*    
*/    
#if (NOISY2 == 1)
    printf("\n\n");
    printSupplySet(&G);
    
    printf("\nWhose Turn: %d\n", G.whoseTurn);
    printf("Coin Qty: %d\n", G.coins);
    
    for (p=0;p<numPlayer;p++){
        printCardSet(p, &G);
    }
#endif
    
    if (failqty > 0){
        printf("TEST FAILED: %d instances\n", failqty);
    } else {
        printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    
    
#if (NOISY2 == 1)
    printf("*** End of Unit Test 2 ***\n");
#endif
    
    return (EXIT_SUCCESS);
}


/*
 *
 */
int asserttrue(int lefty, int righty) {
    if (lefty != righty){
#if (NOISY2 == 1)
        printf("-->  Assert Failed:  %d != %d\n", lefty, righty);
#endif
        return 1;
    }
    
    return 0;
}

/*
 *
 */
void printCardSet(int player, struct gameState* g) {
    
    int i;
    int deckqty, handqty, discardqty;
    char name[MAX_STRING_LENGTH];
    
    printf("\nplayer%d Deck:\n",player);
    deckqty = g->deckCount[player];
    for (i=0;i<deckqty;i++){
        cardNumToName(g->deck[player][i], name);
        printf("%s, ",name);
    }
    printf("\nplayer%d Hand:\n",player);
    handqty = g->handCount[player];
    for (i=0;i<handqty;i++){
        cardNumToName(g->hand[player][i], name);
        printf("%s, ",name);
    }
    printf("\nplayer%d Discard:\n",player);
    discardqty = g->discardCount[player];
    for (i=0;i<discardqty;i++){
        cardNumToName(g->discard[player][i], name);
        printf("%s, ",name);
    }
    printf("\n\n");
}

void printSupplySet(struct gameState* g){
    int i;
    char name[MAX_STRING_LENGTH];
    
    for (i = 0; i < treasure_map+1; i++){
        if (g->supplyCount[i] > -1){
            cardNumToName(i, name);
            printf("%s(%d): %d\n",name,i,g->supplyCount[i]);
        }
    }
}

