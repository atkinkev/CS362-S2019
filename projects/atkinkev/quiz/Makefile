CFLAGS = -Wall -fpic -coverage -lm -std=c99

all: 
	gcc testme.c -g -o testme $(CFLAGS)
	./testme

clean:
	rm -f testme *.gcov *.gcda *.gcno *.o
