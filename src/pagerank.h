#ifndef _ANALYSE_H_
#define _ANALYSE_H_

#include "graph.h"
#include "counter.h"

#define MAX_ITER_COUNT 100
#define LIMITATION 0.0000001

typedef struct _backwardnode{
    int outlinkCount;
    Array *preNodes;
} BackwardNode;

typedef struct _backwardgraph{
    BackwardNode **nodes;
    Array *deadends;

    int capacity;
    int nodeCount;
    int edgeCount;
} BackwardGraph;

typedef struct _prnode{
    int index;
    double pr;
}PRNode;

void destroyBackwardGraph(BackwardGraph *graph);

BackwardGraph *loadBackwardGraph(const char *filename, int nodeCount);

PRNode *computePageRank(BackwardGraph *graph, double jumpProb);

#endif