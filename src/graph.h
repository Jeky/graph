#ifndef _PAGERANK_H_
#define _PAGERANK_H_

#include "utils.h"

#define BUF_SIZE 100

typedef struct _forwardnode{
	Array *nextNodes;
} ForwardNode;

typedef struct _forwardgraph{
	ForwardNode **node;

    int capacity;
    int nodeCount;
    int edgeCount;
} ForwardGraph;

double loadGraphFile(void *graph, const char *filename, BOOL (*lineHandleFun)(void*,int,int));

#endif