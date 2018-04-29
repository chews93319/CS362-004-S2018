
/* 
 * File:   cardtest4.c
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


//set CARD4 to 0 to remove printfs from output
#define CARD4 1


#define TESTCARD "Council Room"


//function prototypes
int asserttrue(int lefty, int righty);
void printSupplySet(struct gameState* g);
void printCardSet(int player, struct gameState* g);



/*
 * Unit Test for Function: council_room
 */
int main(int argc, char** argv) {
    int newDraw = 0;
    int newCards = 0;
    int newBuys = 0;
    int played = 1;
    int extraCoins = 0;
    //int shuffledCards = 0;
    
    
    int i;
    int p;
    int r;
    int handpos = 0;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int numPlayer = 4;
    struct gameState G, testG;
    int optCard, who;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    
    int failqty = 0;
    
    // clear the game state memory space
    memset(&G, 23, sizeof(struct gameState));
    
    
#if (CARD4 == 1)
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
#endif
    
    // ---------- Test 1: cards in deck with unique card(s) on 'top' -------------
    //    mine, remodel, smithy, village
    
    // initialize a new game
    r = initializeGame(numPlayer, k, seed, &G);
    if (r!=0){
        return -1;
    }
    
    
    // prepare the playing hand
    //    append lastpos hand card to 'top' of deck
    //    convert lastpos hand card to council_room
    who = 0;
    optCard = council_room;
    G.deck[who][G.deckCount[who]++] = G.hand[who][G.handCount[who]-1];
    G.hand[who][G.handCount[who]-1] = optCard;
    
    // prepare the deck top cards
    //    player0: mine, minion, steward, tribute
    //    player1: remodel
    //    player2: smithy
    //    player3: village
    
    for (p=0;p<numPlayer;p++){
        G.deck[p][G.deckCount[p]++] = mine + p;
    }
    
    for (i=0;i<3;i++){
        G.deck[who][G.deckCount[who]++] = minion + i;
    }
    
    
    printf(" Test1 Initialized: \n");
    for (p=0;p<numPlayer;p++){
        printCardSet(p, &G);
    }
    
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    // call cardEffect of TESTCARD within test Game
    handpos = G.handCount[who]-1;
    cardEffect(optCard, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    newDraw = 1;
    newCards = 3;
    newBuys = 1;
    played = 1;
    printf("\n\n");
    
    
    printf(" >> Evaluate Assert Test Set 1 << \n");
    
    //playedCardCount + 1
    #if (CARD4 == 1)
    printf("test played count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + played);
    #endif
    failqty += asserttrue(testG.playedCardCount, G.playedCardCount + played);
    
    //playedCard is council_room
    who = 0;
    #if (CARD4 == 1)
    printf("test played cardID = %d, expected = %d\n", testG.playedCards[0], G.hand[who][G.handCount[who]-1]);
    #endif
    failqty += asserttrue(testG.playedCards[0], G.hand[who][G.handCount[who]-1]);
    
    //player0: handCount + newDraw + newCards - played (orig + 1 + 3 - 1)
    who = 0;
    #if (CARD4 == 1)
    printf("test player%d hand count = %d, expected = %d\n", 
            who, testG.handCount[who], G.handCount[who] + newDraw + newCards - played);
    #endif
    failqty+=asserttrue(testG.handCount[who], G.handCount[who] + newDraw + newCards - played);
    
    //all other players: handCount + newDraw
    for (p=1;p<numPlayer;p++){
        #if (CARD4 == 1)
        printf("test player%d hand count = %d, expected = %d\n", 
                p, testG.handCount[p], G.handCount[p] + newDraw);
        #endif
        failqty+=asserttrue(testG.handCount[p], G.handCount[p] + newDraw);
    }
    
    //player0: last drawn card is from deck at position deckCount - newDraw - newCards
    who = 0;
    #if (CARD4 == 1)
    printf("test player%d drawn cardID = %d, expected = %d\n", 
            who, testG.hand[who][testG.handCount[who]-1], G.deck[who][G.deckCount[who]-newDraw-newCards]);
    #endif
    failqty+=asserttrue(testG.hand[who][testG.handCount[who]-1], G.deck[who][G.deckCount[who]-newDraw-newCards]);
    
    //all other players: most recent drawn card is original top deck card
    for (p=1;p<numPlayer;p++){
        #if (CARD4 == 1)
        printf("test player%d drawn cardID = %d, expected = %d\n", p, testG.hand[p][testG.handCount[p]-1], G.deck[p][G.deckCount[p]-1]);
        #endif
        failqty+=asserttrue(testG.hand[p][testG.handCount[p]-1], G.deck[p][G.deckCount[p]-1]);
    }
    
    //player0: deckCount - newDraw - newCards (orig - 1 - 3)
    who = 0;
    #if (CARD4 == 1)
    printf("test player%d deck count = %d, expected = %d\n", 
            who, testG.deckCount[who], G.deckCount[who] - newDraw - newCards);
    #endif
    failqty+=asserttrue(testG.deckCount[who], G.deckCount[who] - newDraw - newCards);
    
    //all other players: deckCount - newDraw
    for (p=1;p<numPlayer;p++){
        #if (CARD4 == 1)
        printf("test player%d hand count = %d, expected = %d\n", 
                p, testG.deckCount[p], G.deckCount[p] - newDraw);
        #endif
        failqty+=asserttrue(testG.deckCount[p], G.deckCount[p] - newDraw);
    }
    
    
    //numActions - played
    who = 0;
    #if (CARD4 == 1)
    printf("test player%d numActions = %d, expected = %d\n", 
            who, testG.numActions, G.numActions - played);
    #endif
    failqty+=asserttrue(testG.numActions, G.numActions - played);
    
    
    //numBuys + newBuys
    who = 0;
    #if (CARD4 == 1)
    printf("test player%d numBuys = %d, expected = %d\n", 
            who, testG.numBuys, G.numBuys + newBuys);
    #endif
    failqty+=asserttrue(testG.numBuys, G.numBuys + newBuys);
    
/*    
    //
    //draw[deckCount-1,deckCount-2,deckCount-3] = hand[handCount-3,handCount-2, handCount-1]
    
    //if draw[] contains treasure cards, then extracoins = qty
    //   testGame.coins = Game.coins + extracoins
    
*/    
    
    
/*    
*/    
#if (CARD4 == 1)
    printf("\n\n");
    
    printf("Test Game Cardset\n");
    for (p=0;p<numPlayer;p++){
        printCardSet(p, &testG);
    }
    
    printf("Seed Game Cardsets\n");
    for (p=0;p<numPlayer;p++){
        printCardSet(p, &G);
    }
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
#if (CARD4 == 1)
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
    printf("\nCommon Played Pile:\n");
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

