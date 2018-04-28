
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

//function prototypes
int asserttrue(int lefty, int righty);
void printSupplySet(struct gameState* g);
void printCardSet(int player, struct gameState* g);



/*
 * Unit Test for Function: gainCard
 */
int main(int argc, char** argv) {
    
//#if (NOISY1 == 1)
    printf("*** Start of Unit Test 1 ***\n");
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
    
#if (NOISY1 == 1)
    if (r >= 0) printf("Game Initialized\n\n");
    
    printSupplySet(&G);
    
    for (p=0;p<numPlayer;p++){
        printCardSet(p, &G);
    }
#endif
    
    /*Gain all of the Smithy Cards into Player Discard Piles*/
    int startDiscard, startDeck, startHand;
    int optDest = 0;
    int startSupply = G.supplyCount[smithy];
    for (i = 0; i < startSupply; i++){
        who = i % 2;
        startDiscard = G.discardCount[who];
        
#if (NOISY1 == 1)
        printf("player%d gain Smithy...\n",who);
#endif
        r = gainCard(smithy, &G, optDest, who);
        failqty += asserttrue(r,0);
        
#if (NOISY1 == 1)
        printf("to discard pile.\n");
#endif
        failqty += asserttrue(startDiscard + 1, G.discardCount[who]);
        failqty += asserttrue(smithy, G.discard[who][startDiscard]);
        
        //test values of toFlag other than the set {1,2}
        if (i == startSupply - 1){
            optDest = -1;
        } else {
            optDest = 3 + i;
        }
    }
    
    /*Gain one Adventurer Card into each Player Decks (top position)*/
    startSupply = G.supplyCount[adventurer];
    optDest = 1;
    for (i = 0; i < 2; i++){
        who = i % 2;
        startDeck = G.deckCount[who];
        
#if (NOISY1 == 1)
        printf("player%d gain Adventurer...\n",who);
#endif
        r = gainCard(adventurer, &G, optDest, who);
        failqty += asserttrue(r,0);
        
#if (NOISY1 == 1)
        printf("to draw pile (deck).\n");
#endif
        failqty += asserttrue(startDeck + 1, G.deckCount[who]);
        failqty += asserttrue(adventurer, G.deck[who][startDeck]);
    }
    
    /*Gain one Gold Card into each Player Hands (last position)*/
    startSupply = G.supplyCount[gold];
    optDest = 2;
    for (i = 0; i < 2; i++){
        who = i % 2;
        startHand = G.handCount[who];
        
#if (NOISY1 == 1)
        printf("player%d gain Gold...\n",who);
#endif
        r = gainCard(gold, &G, optDest, who);
        failqty += asserttrue(r,0);
        
#if (NOISY1 == 1)
        printf("to hand.\n");
#endif
        failqty += asserttrue(startHand + 1, G.handCount[who]);
        failqty += asserttrue(gold, G.hand[who][startHand]);
    }
    
    /*Fail Gain one Smithy for Player0 (empty supply)*/
    who = 0;
#if (NOISY1 == 1)
    printf("player%d fail to gain Smithy (none left).\n",who);
#endif
    r = gainCard(smithy, &G, 2, who);
    failqty += asserttrue(-1, r);
    
    /*Fail Gain Illegal Supply Card Value*/
    who = 0;
#if (NOISY1 == 1)
    printf("player%d fail to gain Illegal Supply Card.\n",who);
#endif
    r = gainCard(57, &G, 2, who);
    failqty += asserttrue(-1, r);
    
    /*Fail Gain to illegal player*/
    who = 5;
#if (NOISY1 == 1)
    printf("(illegal) player%d fail to gain Mine Card.\n",who);
#endif
    r = gainCard(mine, &G, 2, who);
    failqty += asserttrue(-1, r);
    
    
#if (NOISY1 == 1)
    printf("\n\n");
    printSupplySet(&G);
    
    for (p=0;p<numPlayer;p++){
        printCardSet(p, &G);
    }
#endif
    
    if (failqty > 0){
        printf("TEST FAILED: %d instances\n", failqty);
    } else {
        printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    
    
#if (NOISY1 == 1)
    printf("*** End of Unit Test 1 ***\n");
#endif
    
    return (EXIT_SUCCESS);
}


/*
 *
 */
int asserttrue(int lefty, int righty) {
    if (lefty != righty){
#if (NOISY1 == 1)
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
