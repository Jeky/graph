#ifndef _PAGERANK_H_
#define _PAGERANK_H_

#include "utils.h"

#define BUF_SIZE 100

typedef struct _node{
    Array *prevNodes;
    Array *nextNodes;
} Node;


typedef struct _node_array{
    int length;
    Node **values;
    int capacity;
} NodeArray;


typedef struct _graph{
    NodeArray *nodes;
    Array *deadends;
    int edgeCount;
} Graph;


double loadGraphFile(void *graph, const char *filename, BOOL (*lineHandleFun)(void*,int,int,int));

Node *createNode();

void destroyNode(Node *n);

NodeArray *createNodeArray();

NodeArray *createNodeArrayWithCapacity(int capacity);

void destroyNodeArray(NodeArray *nodeArray);

void nodeArrayAdd(NodeArray *nodeArray, Node *val);

Node *nodeArrayGet(NodeArray *nodeArray, int index);

Graph *createGraph();

Graph *createGraphWithNodeCount(int nodeCount);

void destroyGraph(Graph *g);

double loadGraph(Graph *g, const char *filename);

#endif