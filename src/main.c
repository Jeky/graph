#include "graph.h"

int main(){
    Graph *g = createGraph();

    loadGraph(g, "/Users/jeky/data/twitter/twitter-encode.graph");
    printf("Graph(V=%d, E=%d)\n", g->nodes->length, g->edgeCount);
    destroyGraph(g);

    return 0;
}
