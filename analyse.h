#ifndef _ANALYSE_H_
#define _ANALYSE_H_

#include "graph.h"

#define MAX_ITER_COUNT 100
#define LIMITATION 0.0000001

typedef struct _prnode{
    int index;
    double pr;
}PRNode;

typedef struct _degnode{
	int inDeg;
	int outDeg;
}DegNode;

PRNode *computePageRank(Graph *graph, double jumpProb);

#endif