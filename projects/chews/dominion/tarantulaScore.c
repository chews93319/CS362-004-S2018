
/* 
 * File:   tarantulaScore.c
 * Author: Sam Chew
 * ONID: chews 933191613
 *
 * Created on June 1, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "time.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"


//set NOISY to 0 to remove printfs from output
#define NOISY 1
#define ILLEGALPLAYER 0

//function prototypes
int asserttrue(int lefty, int righty);
void printSupplySet(struct gameState* g);
void printCardSet(int player, struct gameState* g);



/*
 * Tarantula Test for Function: scoreFor
 */
int main(int argc, char** argv) {
    
//#if (NOISY == 1)
//    printf("*** Start of Unit Test 4 ***\n");
//#endif
    
    int i, j, p;
    int r;
    int seed = 100;
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
    if (r!=0){
        return -1;
    }
    
    // initialize the random generator
    srand(time(0));
    
#if (NOISY == 1)
    //if (r >= 0) printf("Game Initialized\n\n");
    
    //printSupplySet(&G);
    
    //printf("\n");
    //printf("Whose Turn: %d\n", G.whoseTurn);
    
    //for (p=0;p<numPlayer;p++){
    //    printCardSet(p, &G);
    //}
#endif
    
    int optCard;
    int optPile;
    int pScore;
    char name[MAX_STRING_LENGTH];
    // estate = 1
    // duchy = 2
    // province = 3
    // great_hall = 16
    // curse = 0
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
    
    
    int testType = (rand() % 100) % 4;  //printf("testType:%d\n",testType);
    int cardIndex;
    int cardQty = rand() % 10;
    int expScore;
    
    if (testType == 0){
        #if (NOISY == 1)
        printf("\n  Test with same Treasures in one pile\n");
        printf("----------------------------------------\n");
        #endif
        
        cardIndex = rand() % 5;
        optCard = testCard[cardIndex];
        cardNumToName(optCard, name);
        
        pScore = cardQty * valCard[cardIndex];   printf("pScore:%d\n",pScore);
        
        optPile = rand() % 3;  printf("optPile:%d\n",optPile);
        
        for (i=0;i<cardQty;i++){
        switch (optPile) {
            case 0: G.deck[who][G.deckCount[who]++] = optCard;break;
            case 1: G.hand[who][G.handCount[who]++] = optCard;break;
            case 2: G.discard[who][G.discardCount[who]++] = optCard;break;
        }
        }
        
        
        printCardSet(who, &G);
        
        expScore = scoreFor(1, &G);   //printf("expScore:%d\n",expScore);
        
    }
    
    if (testType == 1){
        #if (NOISY == 1)
        printf("\n  Test with same Treasures in unique piles\n");
        printf("--------------------------------------------\n");
        #endif
        
        cardIndex = rand() % 5;
        optCard = testCard[cardIndex];
        cardNumToName(optCard, name);
        
        pScore = cardQty * valCard[cardIndex];   printf("pScore:%d\n",pScore);
        
        
        
        for (i=0;i<cardQty;i++){
            optPile = rand() % 3;
            switch (optPile) {
                case 0: G.deck[who][G.deckCount[who]++] = optCard;break;
                case 1: G.hand[who][G.handCount[who]++] = optCard;break;
                case 2: G.discard[who][G.discardCount[who]++] = optCard;break;
            }
        }
        
        
        printCardSet(who, &G);
        
        expScore = scoreFor(1, &G);   //printf("expScore:%d\n",expScore);
    }
    
    if (testType == 2){
        #if (NOISY == 1)
        printf("\n  Test with unique Treasures in unique piles\n");
        printf("----------------------------------------------\n");
        #endif
        
        
        pScore = 0;
        
        for (i=0;i<cardQty;i++){
            cardIndex = rand() % 5;
            optCard = testCard[cardIndex];
            cardNumToName(optCard, name);
            
            pScore += valCard[cardIndex];
            
            optPile = rand() % 3;
            switch (optPile) {
                case 0: G.deck[who][G.deckCount[who]++] = optCard;break;
                case 1: G.hand[who][G.handCount[who]++] = optCard;break;
                case 2: G.discard[who][G.discardCount[who]++] = optCard;break;
            }
        }
        
        
        printCardSet(who, &G);
        
        expScore = scoreFor(1, &G);   //printf("expScore:%d\n",expScore);
    }
    
    if (testType == 3){
        #if (NOISY == 1)
        printf("\n  Test with a Garden in a pile (random card Qty)\n");
        printf("--------------------------------------------------\n");
        #endif
        
        
        pScore = 0;
        
        for (i=0;i<cardQty;i++){
            cardIndex = rand() % 5;
            optCard = testCard[cardIndex];
            cardNumToName(optCard, name);
            
            pScore += valCard[cardIndex];
            
            optPile = rand() % 3;
            switch (optPile) {
                case 0: G.deck[who][G.deckCount[who]++] = optCard;break;
                case 1: G.hand[who][G.handCount[who]++] = optCard;break;
                case 2: G.discard[who][G.discardCount[who]++] = optCard;break;
            }
        }
        
        int cardQty = rand() % 55;
        optPile = rand() % 3;
        for (i=0;i<cardQty;i++){
            switch (optPile) {
                case 0: G.deck[who][G.deckCount[who]++] = gold;break;
                case 1: G.hand[who][G.handCount[who]++] = gold;break;
                case 2: G.discard[who][G.discardCount[who]++] = gold;break;
            }
        }
        G.deck[who][G.deckCount[who]++] = gardens;
        
        pScore += (G.deckCount[who] + G.handCount[who] + G.discardCount[who]) / 10;
        
        printCardSet(who, &G);
        
        expScore = scoreFor(1, &G);   //printf("expScore:%d\n",expScore);
        
        
    }
    
    asserttrue(pScore, expScore);
    
    if(pScore != expScore)
        return 1;
    
    return (EXIT_SUCCESS);
}


/*
 *
 */
int asserttrue(int lefty, int righty) {
    if (lefty != righty){
#if (NOISY == 1)
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

