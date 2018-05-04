CFLAGS = -Wall -fpic -coverage -lm

testme.o: testme.c
	gcc -c testme.c -g $(CFLAGS) 

testme: testme.o
	gcc -o testme testme.c -g $(CFLAGS)

all: testme

clean:
	rm -f *.o testme *.gcov *.gcda *.gcno *.so *.out

