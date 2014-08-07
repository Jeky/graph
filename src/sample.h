#ifndef _SAMPLE_H_
#define _SAMPLE_H_

#include "utils.h"
#include "graph.h"

// random node sampling functions
int *randomNodeSample(int nodeCount, int count);

// random edge sampling functions
typedef struct _edge{
	int fromId;
	int toId;
} Edge;

Edge *randomEdgeSample(const char *input, int edgeCount, int count);

// random walk sampling functions
#define JUMP 1
#define WALK 0

typedef struct _forwardnode{
	Array *nextNodes;
} ForwardNode;

typedef struct _forwardgraph{
	ForwardNode **node;

    int nodeCount;
    int edgeCount;
} ForwardGraph;

typedef struct _step{
	int nodeId;
	int tag;
} Step;

Step *randomWalkSample(char *input, int nodeCount, double jp, int count);

#endif