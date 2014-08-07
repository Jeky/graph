#include "counter.h"


BOOL nodeCounter(void *graph, int lineIndex, int fromId, int toId){
    int *max = (int*)graph;
    *max = fromId > toId ? fromId : toId;

    return TRUE;
}

int countNode(const char *filename){
    int maxNodeIndex = 0;
    double totalTime;

    printf("Start Counting Nodes in Graph From File: %s.\n", filename);
    totalTime = loadGraphFile(&maxNodeIndex, filename, &nodeCounter);

    printf("Node Count: %d. Total Time: %0.2lf sec.\n", maxNodeIndex + 1, totalTime);
    return maxNodeIndex + 1;
}


BOOL degreeCounter(void *graph, int lineIndex, int fromId, int toId){
    DegNode *nodes = (DegNode*)graph;
    nodes[fromId].outDeg ++;
    nodes[toId].inDeg ++;

    return TRUE;
}

int indegreeComparator(const void *a, const void *b){
    return ((DegNode*)b)->inDeg - ((DegNode*)a)->inDeg;
}

int outdegreeComparator(const void *a, const void *b){
    return ((DegNode*)b)->outDeg - ((DegNode*)a)->outDeg;
}


DegNode *countDegree(const char *filename, int nodeCount, int sortBy){
    DegNode *nodes;
    double totalTime;
    int i;

    NEW_ARRAY(nodes, DegNode, nodeCount);
    for(i = 0; i < nodeCount; i++){
        nodes[i].index = i;
        nodes[i].inDeg = 0;
        nodes[i].outDeg = 0;
    }

    printf("Start Counting Degree in Graph From File: %s.\n", filename);
    totalTime = loadGraphFile(nodes, filename, &degreeCounter);

    printf("Finish Counting Degree. Total Time: %0.2lf sec.\n", totalTime);
    switch(sortBy){
        case SORT_BY_INDEG:
            printf("Sort Degree by Indegree...\n");
            qsort(nodes, nodeCount, sizeof(DegNode), indegreeComparator);
            break;
        case SORT_BY_OUTDEG:
            printf("Sort Degree by Outdegree...\n");
            qsort(nodes, nodeCount, sizeof(DegNode), outdegreeComparator);
            break;
    }   

    return nodes;
}