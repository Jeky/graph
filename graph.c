#include "graph.h"

Node *createNode(){
    Node *node = NEW(Node);

    CHECK_CONDITION(node != NULL, "Memory Allocation of Node Failed!");

    node->outlinkCount = 0;
    node->preNodes = createArray();

    return node;
}

void destroyNode(Node *node){
    destroyArray(node->preNodes);
    free(node);
}


Graph *createGraph(){
    Graph *graph = NEW(Graph);

    CHECK_CONDITION(graph != NULL, "Memory Allocation of Graph Failed!");

    graph->nodes = NEW_ARRAY(Node*, DEFAULT_ARRAY_SIZE);
    graph->deadends = createArray();
    graph->nodeCount = 0;
    graph->edgeCount = 0;
    graph->capacity = 0;

    CHECK_CONDITION(graph->nodes != NULL, "Memory Allocation of Graph Failed!");

    return graph;
}

void destroyGraph(Graph *graph){
    int i = 0;

    destroyArray(graph->deadends);
    
    for(i = 0; i < graph->nodeCount; i++){
        destroyNode(graph->nodes[i]);
    }
    free(graph->nodes);

    free(graph);
}

void encapsulateGraph(Graph *graph){
    Node **tmp = graph->nodes;
    int i = 0;

    graph->capacity *= 2;
    graph->nodes = NEW_ARRAY(Node*, graph->capacity);

    for(i = 0; i < graph->nodeCount; i++){
        graph->nodes[i] = tmp[i];
    }

    free(tmp);
}

void addNode(Graph *graph, Node *node){
    if(graph->nodeCount == graph->capacity){
        encapsulateGraph(graph);
    }

    graph->nodes[graph->nodeCount++] = node;
}

Graph *loadGraph(const char *filename, int nodeCount){
    Graph *graph = NEW(Graph);
    Node *n;
    int fromId, toId, i;
    clock_t begin, end;
    FILE *fp;

    begin = clock();
    graph->nodes = NEW_ARRAY(Node*, nodeCount);
    graph->deadends = createArray();
    graph->nodeCount = nodeCount;
    graph->edgeCount = 0;
    graph->capacity = nodeCount;

    for(i = 0; i < graph->nodeCount; i++){
        graph->nodes[i] = createNode();
    }

    fp = fopen(filename, "r");
    CHECK_CONDITION(fp != NULL, "Cannot Open Graph File!");

    while(!feof(fp)){
        fscanf(fp, "%d\t%d", &fromId, &toId);
        
        arrayAdd(graph->nodes[toId]->preNodes, fromId);
        graph->nodes[fromId]->outlinkCount++;
        graph->edgeCount ++;
        if(graph->edgeCount % 1000000 == 0){
            printf("read %d lines\n", graph->edgeCount);
        }
    }

    // TODO: check dead ends

    for(i = 0; i < graph->nodeCount; i++){
        if(graph->nodes[i]->outlinkCount == 0){
            arrayAdd(graph->deadends, i);
        }
    }

    end = clock();
    printf("Finish Loading Graph[V = %d, E = %d]. Total Time: %0.2lf\n", 
            graph->nodeCount, graph->edgeCount, (double)(end - begin) / CLOCKS_PER_SEC);

    return graph;
}







