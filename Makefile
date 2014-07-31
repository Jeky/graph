C=clang
CFLAGS=-c -Wall
LDFLAGS=-shared -fPIC
SOURCES=graph.c utils.c analyse.c
OBJECTS=$(SOURCES:.c=.o)
TARLIB=graphlib.so

all: $(SOURCES) $(TARLIB)
	
$(TARLIB): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o *.so