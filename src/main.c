#include "graph.h"


void printGraph(Graph *g){
    int i, j;
    printf("Graph(V=%d, E=%d)\n", g->nodes->length, g->edgeCount);
    printf("Edges (From -> To):\n");
    for(i = 0; i < g->nodes->length; i++){
        for(j = 0; j < g->nodes->values[i]->nextNodes->length; j++){
            printf("%d -> %d\n", i, g->nodes->values[i]->nextNodes->values[j]);
        }
    }
    printf("Edges (To <- From):\n");
    for(i = 0; i < g->nodes->length; i++){
        for(j = 0; j < g->nodes->values[i]->prevNodes->length; j++){
            printf("%d <- %d\n", i, g->nodes->values[i]->prevNodes->values[j]);
        }
    }
}


int main(){
    Graph *g = createGraph();
    loadGraph(g, "/Users/jeky/Desktop/test.graph");

    destroyGraph(g);

    return 0;
}
