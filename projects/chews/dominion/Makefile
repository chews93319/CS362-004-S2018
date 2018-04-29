CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
	#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
	
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: unittest2.c unittest1.c dominion.o interface.o
	echo "   CS362 Spring 2018: Chews" > unittestresults.out
	echo "-------------------------------" >> unittestresults.out
	echo "Assignment-3 Unit Tests Results" >> unittestresults.out
	
	#echo "unittest1.c:" >> unittestresults.out
	#gcc -o unittest1 unittest1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	#unittest1 >> unittestresults.out
	#gcov -b dominion.c >> unittestresults.out
	
	#echo "unittest2.c:" >> unittestresults.out
	#gcc -o unittest2 unittest2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	#unittest2 >> unittestresults.out
	#gcov -b dominion.c >> unittestresults.out
	
	#echo "unittest3.c:" >> unittestresults.out
	#gcc -o unittest3 unittest3.c -g dominion.o rngs.o interface.o $(CFLAGS)
	#unittest3 >> unittestresults.out
	#gcov -b dominion.c >> unittestresults.out
	
	#echo "unittest4.c:" >> unittestresults.out
	#gcc -o unittest4 unittest4.c -g dominion.o rngs.o interface.o $(CFLAGS)
	#unittest4 >> unittestresults.out
	#gcov -b dominion.c >> unittestresults.out
	
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	cat unittestresults.out
	

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out
	rm -f playdom playdom.exe player player.exe testDrawCard testDrawCard.exe
	rm -f unittest1 unittest2 unittest3 unittest4 cardtest1
