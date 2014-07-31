#include "graph.h"
#include "analyse.h"
#include <stdio.h>

int main(int argc, char const *argv[]){
    const char *filename = argv[1];
    int nodeCount = atoi(argv[2]);
    double jumpProb = atof(argv[3]);
    FILE *fp = fopen(argv[4], "w+");

    Graph *g = loadGraph(filename, nodeCount);
    PRNode *prnodes = computePageRank(g, jumpProb);

    printPageRank(prnodes, nodeCount, fp);
    fclose(fp);
    
    destroyGraph(g);
    return 0;
}