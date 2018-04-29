
/* 
 * File:   cardtest3.c
 * Author: Sam Chew
 * ONID: chews 933191613
 *
 * Created on April 28, 2018, 23:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"


//set CARD3 to 0 to remove printfs from output
#define CARD3 1


#define TESTCARD "village"


//function prototypes
int asserttrue(int lefty, int righty);
void printSupplySet(struct gameState* g);
void printCardSet(int player, struct gameState* g);



/*
 * Unit Test for Function: smithy
 */
int main(int argc, char** argv) {
    int newCards = 0;
    int newActions = 0;
    int played = 1;
    int extraCoins = 0;
    //int shuffledCards = 0;
    
    
    //int i;
    int p;
    int r;
    int handpos = 0;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int numPlayer = 2;
    struct gameState G, testG;
    int optCard, optDest, who;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    
    int failqty = 0;
    
    // clear the game state memory space
    memset(&G, 23, sizeof(struct gameState));
    
    
#if (CARD3 == 1)
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    //for (p=0;p<numPlayer;p++){
    //    printCardSet(p, &G);
    //}
#endif
    
    // ---------- Test 1: cards in deck with unique card on 'top' -------------
    
    // initialize a new game
    r = initializeGame(numPlayer, k, seed, &G);
    if (r!=0){
        return -1;
    }
    
    
    // prepare the playing hand
    //    append lastpos hand card to 'top' of deck
    //    convert lastpos hand card to adventurer
    who = 0;
    optCard = village;
    G.deck[who][G.deckCount[who]++] = G.hand[who][G.handCount[who]-1];
    G.hand[who][G.handCount[who]-1] = optCard;
    
    // prepare the deck
    //     mine
    
    G.deck[who][G.deckCount[who]++] = mine;
    
    
    printf(" Test1 Initialized: \n");
    
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    // call cardEffect of TESTCARD within test Game
    handpos = G.handCount[who]-1;
    cardEffect(optCard, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    newCards = 1;
    newActions = 2;
    played = 1;
    printf("\n\n");
    
    
    
    printf(" >> Evaluate Assert Test Set 1 << \n");
    
    //playedCardCount + 1
    #if (CARD3 == 1)
    printf("test played count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + played);
    #endif
    failqty += asserttrue(testG.playedCardCount, G.playedCardCount + played);
    
    //playedCard is village
    #if (CARD3 == 1)
    printf("test played cardID = %d, expected = %d\n", testG.playedCards[0], G.hand[who][G.handCount[who]-1]);
    #endif
    failqty += asserttrue(testG.playedCards[0], G.hand[who][G.handCount[who]-1]);
    
    //handCount + newCard - played  (orig - 1 + 1)
    #if (CARD3 == 1)
    printf("test hand count = %d, expected = %d\n", testG.handCount[who], G.handCount[who] + newCards - played);
    #endif
    failqty+=asserttrue(testG.handCount[who], G.handCount[who] + newCards - played);
    
    //drawn card is mine
    #if (CARD3 == 1)
    printf("test drawn cardID = %d, expected = %d\n", testG.hand[who][testG.handCount[who]-1], G.deck[who][G.deckCount[who]-1]);
    #endif
    failqty += asserttrue(testG.hand[who][testG.handCount[who]-1], G.deck[who][G.deckCount[who]-1]);
    
    //deckCount - newCard
    #if (CARD3 == 1)
    printf("test deck count = %d, expected = %d\n", testG.deckCount[who], G.deckCount[who] - newCards);
    #endif
    failqty += asserttrue(testG.deckCount[who], G.deckCount[who] - newCards);
    
    //numActions - played + newActions
    #if (CARD3 == 1)
    printf("test numActions = %d, expected = %d\n", testG.numActions, G.numActions - played + newActions);
    #endif
    failqty+=asserttrue(testG.numActions, G.numActions - played + newActions);
    
    //
    //draw[deckCount-1,deckCount-2,deckCount-3] = hand[handCount-3,handCount-2, handCount-1]
    
    //if draw[] contains treasure cards, then extracoins = qty
    //   testGame.coins = Game.coins + extracoins
    
    
    
    
/*    
*/    
#if (CARD3 == 1)
    printf("\n\n");
    
    printf("Test Game Cardset\n");
    printCardSet(who, &testG);
    
    printf("Seed Game Cardsets\n");
    printCardSet(who, &G);
    //for (p=0;p<numPlayer;p++){
    //    printCardSet(p, &G);
    //}
#endif
    
    if (failqty > 0){
        printf("TEST FAILED: %d instances\n", failqty);
    } else {
        printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    
    
    
    return (EXIT_SUCCESS);
}


/*
 *
 */
int asserttrue(int lefty, int righty) {
    if (lefty != righty){
#if (CARD3 == 1)
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
    int deckqty, handqty, discardqty, playqty;
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
    printf("\nplayer%d Played:\n",player);
    playqty = g->playedCardCount;
    for (i=0;i<playqty;i++){
        cardNumToName(g->playedCards[i], name);
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

