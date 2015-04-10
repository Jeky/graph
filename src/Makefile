C=clang
CFLAGS=-c -Wall -x c
LDFLAGS=
SHARE_LDFLAGS=-shared -fPIC
SOURCES=graph.c utils.c pagerank.c counter.c sample.c main.c
OBJECTS=$(SOURCES:.c=.o)
TARLIB=graphlib.so
EXEC=graph

#all: $(SOURCES) $(TARLIB)

all: $(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	
$(TARLIB): $(OBJECTS) 
	$(CC) $(SHARE_LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o *.so $(EXEC)