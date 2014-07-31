CC=clang
CFLAGS=-c -Wall

all: pagerank

pagerank: graph.o utils.o analyse.o pagerank.o
	$(CC) graph.o utils.o analyse.o pagerank.o -o pagerank

pagerank.o: pagerank.c
	$(CC) $(CFLAGS) pagerank.c

graph.o: graph.c
	$(CC) $(CFLAGS) graph.c

utils.o: utils.c
	$(CC) $(CFLAGS) utils.c

analyse.o: analyse.c
	$(CC) $(CFLAGS) analyse.c

clean:
	rm *.o pagerank	