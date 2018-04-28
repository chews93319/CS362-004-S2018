
/* 
 * File:   unittest3.c
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
#define NOISY3 1
#define ILLEGALPLAYER 0

//function prototypes
int asserttrue(int lefty, int righty);
void printSupplySet(struct gameState* g);
void printCardSet(int player, struct gameState* g);


/*
 * Unit Test for Function: fullDeckCount
 */
int main(int argc, char** argv) {
    
//#if (NOISY3 == 1)
    printf("*** Start of Unit Test 3 ***\n");
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
    
#if (NOISY3 == 1)
    if (r >= 0) printf("Game Initialized\n\n");
    
    printSupplySet(&G);
    
    printf("\n");
    printf("Whose Turn: %d\n", G.whoseTurn);
    printf("Coin Qty: %d\n", G.coins);
    
    for (p=0;p<numPlayer;p++){
        printCardSet(p, &G);
    }
#endif
    
    who = 0;
    int optDest, optCard;
    int qtyCard;
    char name[MAX_STRING_LENGTH];
    
    for (i = 0; i < 3; i++){
        optCard = adventurer + i;
        optDest = i;
        gainCard(optCard, &G, optDest, who);
    }
    
    // Test card quantities in player0 deck
    optCard = estate;
    qtyCard = fullDeckCount(who, optCard, &G);
#if (NOISY3 == 1)
    cardNumToName(optCard, name);
    printf("player%d has %d %ss.\n",who, qtyCard,name);
#endif
    failqty += asserttrue(qtyCard,3);
    
    optCard = copper;
    qtyCard = fullDeckCount(who, optCard, &G);
#if (NOISY3 == 1)
    cardNumToName(optCard, name);
    printf("player%d has %d %ss.\n",who, qtyCard,name);
#endif
    failqty += asserttrue(qtyCard,7);
    
    for (i = 0; i < 3; i++){
        optCard = adventurer + i;
        qtyCard = fullDeckCount(who, optCard, &G);
        failqty += asserttrue(qtyCard,1);
#if (NOISY3 == 1)
        cardNumToName(optCard, name);
        printf("player%d has %d %s.\n",who, qtyCard,name);
#endif
    }
    
    optCard = province;
    qtyCard = fullDeckCount(who, optCard, &G);
#if (NOISY3 == 1)
    cardNumToName(optCard, name);
    printf("player%d has %d %ss.\n",who, qtyCard,name);
#endif
    failqty += asserttrue(qtyCard,0);
    
#if (ILLEGALPLAYER == 1)    
    // Test card quantities in (illegal) player2 deck
    who = 2;
    optCard = estate;
    qtyCard = fullDeckCount(who, optCard, &G);
#if (NOISY3 == 1)
    cardNumToName(optCard, name);
    printf("player%d has %d %ss.\n",who, qtyCard,name);
#endif
    failqty += asserttrue(qtyCard,0);
#endif
    
    
    
#if (NOISY3 == 1)
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
    
    
#if (NOISY3 == 1)
    printf("*** End of Unit Test 3 ***\n");
#endif
    
    return (EXIT_SUCCESS);
}


/*
 *
 */
int asserttrue(int lefty, int righty) {
    if (lefty != righty){
#if (NOISY3 == 1)
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

