#include "graph.h"

Node *createNode(){
    Node *node;
    NEW(node, Node);

    node->outlinkCount = 0;
    node->preNodes = createArray();

    return node;
}

void destroyNode(Node *node){
    destroyArray(node->preNodes);
    free(node);
}

Graph *createGraphWithNodeCount(int nodeCount){
    Graph *graph;
    NEW(graph, Graph);

    NEW_ARRAY(graph->nodes, Node*, nodeCount);
    graph->deadends = createArray();
    graph->nodeCount = 0;
    graph->edgeCount = 0;
    graph->capacity = nodeCount;

    return graph;
}

Graph *createGraph(){
    return createGraphWithNodeCount(DEFAULT_ARRAY_SIZE);
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

    graph->capacity += DEFAULT_ARRAY_SIZE;
    NEW_ARRAY(graph->nodes, Node*, graph->capacity);

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
    Graph *graph;
    int fromId, toId, i;
    clock_t begin, end;
    FILE *fp;

    printf("Start Loading Graph From File: %s.\n", filename);
    begin = clock();

    graph = createGraphWithNodeCount(nodeCount);

    for(i = 0; i < nodeCount; i++){
        addNode(graph, createNode());
    }

    fp = fopen(filename, "r");
    CHECK_CONDITION(fp != NULL, "Cannot Open Graph File!");

    while(!feof(fp)){
        fscanf(fp, "%d\t%d", &fromId, &toId);
        
        CHECK_CONDITION(graph->nodes[toId] && graph->nodes[fromId], "Init Graph Error!");

        arrayAdd(graph->nodes[toId]->preNodes, fromId);
        graph->nodes[fromId]->outlinkCount++;
        graph->edgeCount ++;
        if(graph->edgeCount % 1000000 == 0 && graph->edgeCount != 0){
            printf("read %d lines\n", graph->edgeCount);
        }
    }

    // check dead ends
    printf("Checking Deadends...\n");
    for(i = 0; i < graph->nodeCount; i++){
        if(i % 100000 == 0 && i != 0){
            printf("Checked %d nodes. Dead Ends Count: %d\n", i, graph->deadends->length);
        }
        if(graph->nodes[i]->outlinkCount == 0){
            arrayAdd(graph->deadends, i);
        }
    }

    fclose(fp);
    end = clock();
    printf("Finish Loading Graph[V = %d, E = %d, D = %d]. Total Time: %0.2lf sec.\n", 
            graph->nodeCount, graph->edgeCount, graph->deadends->length,
            (double)(end - begin) / CLOCKS_PER_SEC);

    return graph;
}







