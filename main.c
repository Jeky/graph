#include "graph.h"
#include <stdio.h>

int main(int argc, char const *argv[]){
    Graph *g = loadGraph(argv[1]);

    destroyGraph(g);
    return 0;
}