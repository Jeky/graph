#include "graph.h"

double loadGraphFile(void *graph, const char *filename, BOOL (*lineHandleFun)(void*,int,int,int)){
    int fromId, toId, lineCounter = 0, count;
    clock_t begin, end;
    FILE *fp;

    begin = clock();

    fp = fopen(filename, "r");
    CHECK_CONDITION(fp != NULL, "Cannot Open Graph File!");

    while(!feof(fp)){
        count = fscanf(fp, "%d\t%d", &fromId, &toId);
        if(count != 2){ // check reading count of ids
            continue;
        }

        if(!lineHandleFun(graph, lineCounter, fromId, toId)){
            break;
        }

        if(lineCounter % 1000000 == 0 && lineCounter != 0){
            logMsg("read %d lines\n", lineCounter);
        }
        lineCounter += 1;
    }

    fclose(fp);
    end = clock();

    return (double)(end - begin) / CLOCKS_PER_SEC;
}


Node *createNode(){
    Node *n;
    NEW(n, Node);

    n->prevNodes = createArray();
    n->nextNodes = createArray();

    return n;
}


void destroyNode(Node *n){
    destroyArray(n->prevNodes);
    destroyArray(n->nextNodes);

    free(n);
}


NodeArray *createNodeArrayWithCapacity(int capacity){
    NodeArray *array;
    NEW(array, NodeArray);

    array->length = 0;
    array->capacity = capacity;
    NEW_ARRAY(array->values, Node*, array->capacity);

    return array;
}


NodeArray *createNodeArray(){
    return createNodeArrayWithCapacity(DEFAULT_ARRAY_SIZE);
}


void destroyNodeArray(NodeArray *array){
    int i;

    for(i = 0; i < array->length; i++){
        destroyNode(array->values[i]);
    }

    free(array->values);
    free(array);
}


void encapsulateNodeArray(NodeArray *array){
    Node **tmp = array->values;
    int originalLen = array->length;

    array->capacity *= 2;
    NEW_ARRAY(array->values, Node*, array->capacity);

    printf("encapsulateNodeArray from %d to %d\n", originalLen, array->capacity);

    memcpy(array->values, tmp, sizeof(Node*) * originalLen);
    free(tmp);
}


void nodeArrayAdd(NodeArray *array, Node *val){
    if(array->length == array->capacity){
        encapsulateNodeArray(array);
    }

    array->values[array->length++] = val;
}


Node *nodeArrayGet(NodeArray *array, int index){
    CHECK_CONDITION(index < array->length, "Index Out of Bound.");

    return array->values[index];
}


Graph *createGraphWithNodeCount(int nodeCount){
    Graph *g;
    int i;
    NEW(g, Graph);

    g->nodes = createNodeArrayWithCapacity(nodeCount);
    g->deadends = createArray();
    g->edgeCount = 0;

    for(i = 0; i < nodeCount; i++){
        nodeArrayAdd(g->nodes, createNode());
    }

    return g;
}


Graph *createGraph(){
    return createGraphWithNodeCount(DEFAULT_ARRAY_SIZE);
}


void destroyGraph(Graph *g){
    destroyNodeArray(g->nodes);
    destroyArray(g->deadends);

    free(g);
}


BOOL GraphLoader(void *graph, int lineIndex, int fromId, int toId){
    Graph *g = (Graph*)graph;
    while(fromId >= g->nodes->length){
        nodeArrayAdd(g->nodes, createNode());
    }
    while(toId >= g->nodes->length){
        nodeArrayAdd(g->nodes, createNode());
    }

    arrayAdd(g->nodes->values[fromId]->nextNodes, toId);
    arrayAdd(g->nodes->values[toId]->prevNodes, fromId);

    g->edgeCount++;

    return TRUE;
}


double loadGraph(Graph *g, const char *filename){
    return loadGraphFile(g, filename, GraphLoader);
}