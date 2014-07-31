#include "graph.h"

Node *createNode(){
    Node *node = NEW(Node);

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

    graph->nodes = NEW_ARRAY(Node*, DEFAULT_ARRAY_SIZE);
    graph->deadends = createArray();
    graph->nodeCount = 0;
    graph->edgeCount = 0;
    graph->capacity = 0;

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

Graph *loadGraph(const char *filename){
    Graph *graph = createGraph();
    Node *n;
    int fromId, toId;

    FILE *fp = fopen(filename, "r");
    CHECK_CONDITION(fp != NULL, "Cannot Open Graph File!");

    while(!feof(fp)){
        fscanf(fp, "%d\t%d", &fromId, &toId);
        printf("%d\t%d\n", fromId, toId);
        // TODO: construct graph
        while(graph->capacity < fromId){
            
        }
    }

    return graph;
}







