CC=clang
CFLAGS=-c -Wall

all: graphlib.so

graphlib.so: graph.o utils.o analyse.o
	$(CC) -shared -fPIC graph.o utils.o analyse.o -o graphlib.so

graph.o: graph.c
	$(CC) $(CFLAGS) graph.c

utils.o: utils.c
	$(CC) $(CFLAGS) utils.c

analyse.o: analyse.c
	$(CC) $(CFLAGS) analyse.c

clean:
	rm *.o *.so