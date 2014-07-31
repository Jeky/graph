CC=clang
CFLAGS=-c -Wall

all: main.o graph.o utils.o
	$(CC) main.o graph.o utils.o -o graphtool

main.o: main.c graph.o
	$(CC) $(CFLAGS) main.c

graph.o: graph.c utils.o
	$(CC) $(CFLAGS) graph.c

utils.o: utils.c
	$(CC) $(CFLAGS) utils.c

clean:
	rm *.o graphtool