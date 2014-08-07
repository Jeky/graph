#ifndef _COUNTER_H_
#define _COUNTER_H_

#include "graph.h"

#define SORT_BY_INDEX 0
#define SORT_BY_INDEG 1
#define SORT_BY_OUTDEG 2

typedef struct _degnode{
    int index;
    int inDeg;
    int outDeg;
}DegNode;

int countNode(const char *filename);

DegNode *countDegree(const char *filename, int nodeCount, int sortBy);

#endif