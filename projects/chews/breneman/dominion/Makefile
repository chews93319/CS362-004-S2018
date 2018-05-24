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

peertestresults.out: randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o interface.o #
	echo "   CS362 Spring 2018: Chews" > peertestresults.out
	echo "-------------------------------" >> peertestresults.out
	echo "Assignment-5 PeerReview Tests Results" >> peertestresults.out
	
	#causes Segmentation Fault
	#echo "cardtest1.c:" >> peertestresults.out
	#gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	#cardtest1 >> peertestresults.out
	#gcov -b dominion.c >> peertestresults.out
	
	echo "cardtest2.c:" >> peertestresults.out
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	cardtest2 >> peertestresults.out
	gcov -b dominion.c >> peertestresults.out
	
	echo "cardtest3.c:" >> peertestresults.out
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o interface.o $(CFLAGS)
	cardtest3 >> peertestresults.out
	gcov -b dominion.c >> peertestresults.out
	
	echo "randomtestcard1.c:" >> peertestresults.out
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	randomtestcard1 >> peertestresults.out
	gcov -b dominion.c >> peertestresults.out
	
	echo "randomtestcard2.c:" >> peertestresults.out
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	randomtestcard2 >> peertestresults.out
	gcov -b dominion.c >> peertestresults.out
	
	#causes Segmentation Fault
	#echo "randomtestcard3.c:" >> peertestresults.out
	#gcc -o randomtestcard3 randomtestcard3.c -g dominion.o rngs.o interface.o $(CFLAGS)
	#randomtestcard3 >> peertestresults.out
	#gcov -b dominion.c >> peertestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out
	rm -f playdom playdom.exe player player.exe testDrawCard testDrawCard.exe
	rm -f cardtest1 cardtest2 cardtest3
	rm -f randomtestcard1 randomtestcard2 randomtestcard3
