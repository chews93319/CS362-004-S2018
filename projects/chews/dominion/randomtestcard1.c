
/* 
 * File:   randomtestcard1.c
 * Author: Sam Chew
 * ONID: chews 933191613
 *
 * Created on May 12, 2018, 23:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

//set CARD1 to 0 to remove printfs from output
#define RNDCARD1 1
#define STCRND1  0
  //       1    print G state startup info
  //       2    printCardSet(G) prior to clone
  //       4    printCardSet(testG) after cardEffect


#define TESTCARD "adventurer"

#define MOSTHAND     8
#define MOSTDECK    40
#define MOSTDISCARD 40
#define SUPPLYSIZE  17

//function prototypes
int assertEQ(char *prefix, int lefty, int righty);
void printSupplySet(struct gameState* g);
void printCardSet(int player, struct gameState* g);
void randtest1(void);
int myRand(int maxVal);
void testRNGS(void);


/*
 * Random Test Generator for Dominion Card: adventurer
 */
int main(int argc, char** argv) {
    
    SelectStream(0);  // Select the default stream
    PlantSeeds(-1);    // Set the State of all streams
    
    //testRNGS();
    randtest1();
    return 0;
}

/*
 * Card Specific Test Implementation
 */
void randtest1(void){
    //establish test operating variables
    int tcCount = 0;
    time_t start;
    time_t now;
    double seconds = 0;
    
    //establish game environment variables
    int newDraw = 0;
    int newCards = 0;
    int newBuys = 0;
    int played = 1;
    int discarded = 0;
    int extraCoins = 0;
    //int shuffledCards = 0;
    
    int i;
    int p;
    int r;
    int handpos;
    int choice1;
    int choice2;
    int choice3;
    int bonus;
    //int remove1, remove2;
    int seed = 1000;
    int numPlayer;
    struct gameState G, cntlG,testG;
    int optCard;
    char name[MAX_STRING_LENGTH];
    char msg[MAX_STRING_LENGTH];
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    int supply[SUPPLYSIZE] = {curse, estate, duchy, province,copper, silver, gold,
                adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    
    //establish test evaluation variables
    int failqty;
    int startHandQty, startDeckQty, startDiscardQty;
    int activePlayer;
    
    
    
    
    
    
    time(&start);  //get current time; same as: start = time(NULL)
    
    do {
        //increment test iteration quantity
        tcCount++;
        //#if (RNDCARD1 == 1)
        printf("------------ Testing Card: %s ----- Iteration: %5d ----------------\n", TESTCARD, tcCount);
        //#endif
        
        //reset test operating variables
        failqty = 0;
        
        //re-initialize game state variables
        newDraw = 0;
        newCards = 0;
        newBuys = 0;
        played = 1;
        //extraCoins = 0;
        //shuffledCards = 0;
        handpos = 0;
        choice1 = 0;
        choice2 = 0;
        choice3 = 0;
        bonus = 0;
        // generate a random quantity of players 2,3,4
        numPlayer = 2 + myRand(3);
        #if (STCRND1 && 1)
        printf("player qty:%d\n",numPlayer);
        #endif
        
        // clear the game state memory space
        memset(&G, 23, sizeof(struct gameState));
        memset(&testG, 23, sizeof(struct gameState));
    
        // initialize a control game
        r = initializeGame(numPlayer, k, ++seed, &G);
        if (r!=0){
            printf("iteration %d: initializeGame failure\n", tcCount);
            failqty++;
            continue;
        }
        
        // prepare the conditions of the game
        activePlayer = myRand(numPlayer);
        
        startHandQty = 1 + myRand(MOSTHAND);
        handpos = myRand(startHandQty);
        startDeckQty = 1 + myRand(MOSTDECK);
        startDiscardQty = 1 + myRand(MOSTDISCARD);
        
        
        #if (STCRND1 && 1)
        printf("active player:%d\n",activePlayer);
        printf("testcard handpos:%d\n",handpos);
        printf("HandQty:%d, DeckQty:%d, DiscardQty:%d\n",startHandQty,startDeckQty,startDiscardQty);
        #endif
        
        
        G.handCount[activePlayer] = 0;
        G.coins = 0;
        for(i = 0; i < startHandQty; i++){
            if(i == handpos){
                optCard = adventurer;
            } else {
                optCard = supply[myRand(SUPPLYSIZE)];
            }
            G.hand[activePlayer][G.handCount[activePlayer]++] = optCard;
            if(optCard == copper){ G.coins+=1; }
            if(optCard == silver){ G.coins+=2; }
            if(optCard == gold){ G.coins+=3; }
        }
        
        G.deckCount[activePlayer] = 0;
        for(i = 0; i < startDeckQty; i++){
            if(i % 10 == 0){     //if startDeckQty > 10, at least 1 coin will be present
                optCard = 4 + myRand(3);   //copper=4+0, silver=4+1, gold=4+2
            } else {
                optCard = supply[myRand(SUPPLYSIZE)];
            }
            G.deck[activePlayer][G.deckCount[activePlayer]++] = optCard;
        }
        
        for(i = 0; i < startDiscardQty; i++){
            optCard = supply[myRand(SUPPLYSIZE)];
            G.discard[activePlayer][G.discardCount[activePlayer]++] = optCard;
        }
        
        
        G.whoseTurn = activePlayer;
        G.numActions = 1;
        G.numBuys = 1;
        
        
        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));
        memcpy(&cntlG, &G, sizeof(struct gameState));
        
        // call cardEffect of TESTCARD within test Game
        optCard = adventurer;
        cardEffect(optCard, choice1, choice2, choice3, &testG, handpos, &bonus);
        
        
        
        // manually update control Game state
        //    calculate the number of cards that would:
        //      move from deck to hand
        //      move from deck to discard
        i = G.deckCount[activePlayer]-1;
        newCards = 0;
        discarded = 0;
        extraCoins = 0;
        int temphand[MAX_HAND];
        
        do {
            cardNumToName(cntlG.deck[activePlayer][i], name);
            if((cntlG.deck[activePlayer][i]==copper)||(cntlG.deck[activePlayer][i]==silver)||(cntlG.deck[activePlayer][i]==gold)){
                #if (STCRND1 && 4)
                printf("draw to hand a %s\n",name);
                #endif
                newCards++;
                extraCoins += cntlG.deck[activePlayer][i] - 3;
                cntlG.hand[activePlayer][cntlG.handCount[activePlayer]++] = cntlG.deck[activePlayer][i];
            } else {
                #if (STCRND1 && 4)
                printf("draw to discard a %s\n",name);
                #endif
                
                temphand[discarded] = cntlG.deck[activePlayer][i];
                discarded++;
                //cntlG.discard[activePlayer][cntlG.discardCount[activePlayer]++] = cntlG.deck[activePlayer][i];
            }
            
            //remove the card from 'top of deck' and decrement deckCount
            cntlG.deck[activePlayer][cntlG.deckCount[activePlayer]--] = -1;
            
            i--;
            
        } while ((i>=0) && (newCards<2));
        
        for (i=discarded;i > 0;i--){
            cntlG.discard[activePlayer][cntlG.discardCount[activePlayer]++] = temphand[i-1];
            temphand[i-1] = -1;
        }
                
        played = 1;
        
        
        //playedCardCount + 1
        sprintf(msg, "Test Played (card) Count");
        failqty += assertEQ(msg, testG.playedCardCount, G.playedCardCount + played);
        
        //handCount + 2   (orig - 1 + 3)
        sprintf(msg, "Test Hand (card) Count");
        failqty += assertEQ(msg, testG.handCount[activePlayer], G.handCount[activePlayer] + newCards - played);
        
        //deckCount - newCards - discarded
        sprintf(msg, "Test Deck (card) Count");
        failqty += assertEQ(msg, testG.deckCount[activePlayer], G.deckCount[activePlayer] - newCards - discarded);
        
        //discardCount + discarded
        sprintf(msg, "Test Discard (card) Count");
        failqty += assertEQ(msg, testG.discardCount[activePlayer], G.discardCount[activePlayer] + discarded);
        
        //numActions - played
        sprintf(msg, "Test Action Count");
        failqty += assertEQ(msg, testG.numActions, G.numActions - played);
        
        //if draw[] contains treasure cards, then extracoins = qty
        //   testGame.coins = Game.coins + extracoins
        sprintf(msg, "Test Total Coin Value");
        failqty += assertEQ(msg, testG.coins, G.coins + extraCoins);
        
        
        
        #if (RNDCARD1 == 1)
        if (failqty > 0){
            printf("\n");
            printf("   ---  Initial GameState  ---   \n");
            printCardSet(activePlayer, &G);
            //printf("   ---  Control GameState  ---   \n");
            //printCardSet(activePlayer, &cntlG);
            printf("  ---  Experiment GameState  ---   \n");
            printCardSet(activePlayer, &testG);
        }
        #endif
        
        printf("\n\n");
        
        now = time(NULL);
        seconds = difftime(now, start);
    } while (tcCount < 50);//(seconds < 295);
    
    
    
    
}


/*
 *
 */
int assertEQ(char *prefix, int lefty, int righty) {
    if (lefty != righty){
//#if (RNDCARD1 == 1)
        printf("%s -->  Assert EQUAL Failed:  %d != %d\n", prefix, lefty, righty);
//#endif
        memset(prefix,'\0',MAX_STRING_LENGTH);
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
    
    printf("\nplayer%d Hand(%d)($%d): ",player, g->handCount[player],g->coins);
    handqty = g->handCount[player];
    for (i=0;i<handqty;i++){
        cardNumToName(g->hand[player][i], name);
        printf("%s, ",name);
    }
    printf("\nplayer%d Deck(%d): ",player, g->deckCount[player]);
    deckqty = g->deckCount[player];
    for (i=0;i<deckqty;i++){
        cardNumToName(g->deck[player][i], name);
        printf("%s, ",name);
    }
    printf("\nplayer%d Discard(%d): ",player, g->discardCount[player]);
    discardqty = g->discardCount[player];
    for (i=0;i<discardqty;i++){
        cardNumToName(g->discard[player][i], name);
        printf("%s, ",name);
    }
    printf("\n\n");
}

/*
 *
 */
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

/*
 *  Generate a random integer between 0 and maxVal, inclusively
 */
int myRand(int maxVal){
    //int randInt = (int)(100 * Random());
    //return (maxVal * randInt) % maxVal;
    
    int newStream = (int)(256 * 10 * Random()) % 256;
    //printf("Change to Stream: %d\n",newStream);
    SelectStream(newStream);
    
    int test = (int)(maxVal * 10 * Random()) % maxVal;
    return test;
}


/*
 *  Function for Testing RNGS Implementation
 */
void testRNGS(void){
    int i;
    int test;
    int randval;
    //double u;
    
    
    for(i=0;i < 10000;i++){
        //u = 3 * Random();
        //test = (int) u;
        //test = test % 3;
        //printf(" %f -> %d\n", u, test);
        
        // generates a random value between 0 to randval-1
        randval = 3;
        //test = (int)(randval * Random()) % randval;
        test = myRand(randval);
        printf("%d\n",test);
    }
}
