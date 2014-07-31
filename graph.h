#ifndef _PAGERANK_H_
#define _PAGERANK_H_

#include "utils.h"

typedef struct _node{
    int outlinkCount;
    Array *preNodes;
} Node;

typedef struct _graph{
    Node **nodes;
    Array *deadends;

    int capacity;
    int nodeCount;
    int edgeCount;
} Graph;


/**
 * Node functions
 */
Node *createNode();

void destroyNode(Node *node);


/**
 * Graph functions
 */
Graph *createGraph();

Graph *createGraphWithNodeCount(int nodeCount);

void destroyGraph(Graph *graph);

void addNode(Graph *graph, Node *node);

Graph *loadGraph(const char *filename, int nodeCount);



#endif