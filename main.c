#include "graph.h"
#include <stdio.h>

int main(int argc, char const *argv[]){
    const char *filename = argv[1];
    int nodeCount = atoi(argv[2]);

    Graph *g = loadGraph(filename, nodeCount);

    destroyGraph(g);
    return 0;
}