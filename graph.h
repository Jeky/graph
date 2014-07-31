#ifndef _PAGERANK_H_
#define _PAGERANK_H_

#include "utils.h"

#define DEFAULT_ARRAY_SIZE 128

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

void destroyGraph(Graph *graph);

void addNode(Graph *graph, Node *node);

Graph *loadGraph(const char *filename);



#endif