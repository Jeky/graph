#include "graph.h"
#include "pagerank.h"

int main(){     
    // Graph *g = createGraph();
    // Graph *g = createGraphWithNodeCount(41652230);
 
    // loadGraph(g, "/Users/jeky/data/twitter/twitter-encode.graph");
    // printf("Graph(V=%d, E=%d)\n", g->nodes->length, g->edgeCount);
    // destroyGraph(g);

    BackwardGraph *g = loadBackwardGraph("/Users/jeky/data/twitter/twitter-encode.graph", 41652230);

    printf("Graph(V=%d, E=%d)\n", g->nodeCount, g->edgeCount);
    destroyBackwardGraph(g);

    return 0;
}
