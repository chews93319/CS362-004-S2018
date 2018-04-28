
/* 
 * File:   unittest4.c
 * Author: Sam Chew
 * ONID: chews 933191613
 *
 * Created on April 27, 2018, 17:53:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"


//set NOISY4 to 0 to remove printfs from output
#define NOISY4 1
#define ILLEGALPLAYER 0

//function prototypes
int asserttrue(int lefty, int righty);
void printSupplySet(struct gameState* g);
void printCardSet(int player, struct gameState* g);



/*
 * Unit Test for Function: scoreFor
 */
int main(int argc, char** argv) {
    
//#if (NOISY4 == 1)
    printf("*** Start of Unit Test 4 ***\n");
//#endif
    
    int i, j, p;
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
    
#if (NOISY4 == 1)
    if (r >= 0) printf("Game Initialized\n\n");
    
    //printSupplySet(&G);
    
    //printf("\n");
    //printf("Whose Turn: %d\n", G.whoseTurn);
    
    //for (p=0;p<numPlayer;p++){
    //    printCardSet(p, &G);
    //}
#endif
    
    int optCard, qtyCard;
    int pScore;
    char name[MAX_STRING_LENGTH];
    int testCard[] = {1, 2, 3, 16, 0};
    int valCard[] = {1,3,6, 1, -1};
    
    
    //Start by removing initialized estates cards
    for (p=0;p<numPlayer;p++){
        who = p;
        for (i=0;i < G.deckCount[who];i++){
            if (G.deck[who][i] == estate) {G.deck[who][i] = copper;};
        }
        for (i=0;i < G.handCount[who];i++){
            if (G.hand[who][i] == estate) {G.hand[who][i] = copper;};
        }
    }
    
    
    
    //Test basic victory cards in single piles    
    //    Loop through: estates, duchys, provinces, great halls, curses
    who = 1;
    for(i=0;i<5;i++){
        optCard = testCard[i];
        cardNumToName(optCard, name);
        
        #if (NOISY4 == 1)
        printf("\n  Test with %s cards \n------------------------------\n", name);
        printf("All of Player 1 cards in deck, including %ss\n", name);
        #endif
        for (j=0;j < 3;j++){
            G.deck[who][j] = optCard;
        }
        pScore = scoreFor(who, &G);
        if(asserttrue(pScore, 3*valCard[i])){
            failqty++;
            #if (NOISY4 == 1)
            printCardSet(1, &G);
            #endif
        }
        
        #if (NOISY4 == 1)
        printf("All of Player 1 cards in hand, including %ss\n", name);
        #endif
        for (j=0;j < G.deckCount[who];j++){
            G.hand[who][G.handCount[who]++] = G.deck[who][j];
            G.deck[who][j] = -1;
        }
        G.deckCount[who] = 0;
        pScore = scoreFor(who, &G);
        if(asserttrue(pScore, 3*valCard[i])){
            failqty++;
            #if (NOISY4 == 1)
            printCardSet(1, &G);
            #endif
        }
        
        #if (NOISY4 == 1)
        printf("All of Player 1 cards in discard, including %ss\n", name);
        #endif
        for (j=0;j < G.handCount[who];j++){
            G.discard[who][G.discardCount[who]++] = G.hand[who][j];
            G.hand[who][j] = -1;
        }
        G.handCount[who] = 0;
        pScore = scoreFor(who, &G);
        if(asserttrue(pScore, 3*valCard[i])){
            failqty++;
            #if (NOISY4 == 1)
            printCardSet(1, &G);
            #endif
        }
        
        
        //Return all the cards to the deck and convert to all coppers
        for (j=0;j < G.discardCount[who];j++){
            G.deck[who][G.deckCount[who]++] = copper;
            G.discard[who][j] = -1;
        }
        G.discardCount[who] = 0;
        
    }
    
    
    //Test basic victory cards in multiple piles    
    //    Loop through: estates, duchys, provinces, great halls, curses
    who = 0;
    for(i=0;i<5;i++){
        optCard = testCard[i];
        cardNumToName(optCard, name);
        
        #if (NOISY4 == 1)
        printf("\n  Test with %s cards \n------------------------------\n", name);
        printf("Cards spread (1ea) in piles of Player 0, including %ss\n", name);
        #endif
        
        if (G.handCount[who] >= 1) {
            G.hand[who][G.handCount[who]-1] = optCard;
        } else {
            G.hand[who][G.handCount[who]++] = optCard;
        }
        
        if (G.deckCount[who] >= 1) {
            G.deck[who][G.deckCount[who]-1] = optCard;
        } else {
            G.deck[who][G.deckCount[who]++] = optCard;
        }
        
        if (G.discardCount[who] >= 1) {
            G.discard[who][G.discardCount[who]-1] = optCard;
        } else {
            G.discard[who][G.discardCount[who]++] = optCard;
        }
        
        
        pScore = scoreFor(who, &G);
        if(asserttrue(pScore, 3*valCard[i])){
            failqty++;
            #if (NOISY4 == 1)
            printCardSet(0, &G);
            #endif
        }
        
        
    }
    
    
    
    
    
    
    
    
    /*
    who = 1;
    optCard = gardens;
    cardNumToName(optCard, name);
    
    #if (NOISY4 == 1)
    printf("\n  Test with %s cards \n------------------------------\n", name);
    printf("All of Player 1 cards in deck, including %ss\n", name);
    #endif
    
    //starting with 10 cards, check gardens scores correctly
    //............
    */
    
#if (ILLEGALPLAYER == 1)    
    
#endif
    
    
    
#if (NOISY4 == 1)
    printf("\n\n");
    //printSupplySet(&G);
    
    
    for (p=0;p<numPlayer;p++){
        printCardSet(p, &G);
    }
#endif
    
    if (failqty > 0){
        printf("TEST FAILED: %d instances\n", failqty);
    } else {
        printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    
    
#if (NOISY4 == 1)
    printf("*** End of Unit Test 4 ***\n");
#endif
    
    return (EXIT_SUCCESS);
}


/*
 *
 */
int asserttrue(int lefty, int righty) {
    if (lefty != righty){
#if (NOISY4 == 1)
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

