
/* 
 * File:   randomtestcard2.c
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

//set CARD2 to 0 to remove printfs from output
#define RNDCARD2 1


#define TESTCARD "village"

//function prototypes
int assertEQ(int lefty, int righty);
void printSupplySet(struct gameState* g);
void printCardSet(int player, struct gameState* g);
void randtest1(void);
void testRNGS(void);


/*
 * Random Test Generator for Dominion Card: village
 */
int main(int argc, char** argv) {
    
    SelectStream(0);  // Select the default stream
    PlantSeeds(-1);    // Set the State of all streams
    
    randtest1();
    return 0;
}

/*
 * Card Specific Test Implementation
 */
void randtest1(void){
    int tcCount = 0;
    time_t start;
    time_t now;
    double seconds = 0;
    
    time(&start);  //get current time; same as: start = time(NULL)
    
    do {
        tcCount++;
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        now = time(NULL);
        seconds = difftime(now, start);
    } while (seconds < 295);
    
}


/*
 *
 */
int assertEQ(int lefty, int righty) {
    if (lefty != righty){
#if (CARD1 == 1)
        printf("-->  Assert EQUAL Failed:  %d != %d\n", lefty, righty);
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



