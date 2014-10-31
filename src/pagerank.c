#include "pagerank.h"
#include <math.h>

BackwardNode *createBackwardNode(){
    BackwardNode *node;
    NEW(node, BackwardNode);

    node->outlinkCount = 0;
    node->preNodes = createArray();

    return node;
}

void destroyBackwardNode(BackwardNode *node){
    destroyArray(node->preNodes);
    free(node);
}

BackwardGraph *createBackwardGraph(int nodeCount){
    BackwardGraph *graph;
    NEW(graph, BackwardGraph);

    NEW_ARRAY(graph->nodes, BackwardNode*, nodeCount);
    graph->deadends = createArray();
    graph->nodeCount = 0;
    graph->edgeCount = 0;
    graph->capacity = nodeCount;

    return graph;
}

void destroyBackwardGraph(BackwardGraph *graph){
    int i = 0;

    destroyArray(graph->deadends);
    
    for(i = 0; i < graph->nodeCount; i++){
        destroyBackwardNode(graph->nodes[i]);
    }
    free(graph->nodes);

    free(graph);
}


BOOL backwardGraphLoader(void *g, int lineIndex, int fromId, int toId){
    BackwardGraph* graph = (BackwardGraph*)g;

    CHECK_CONDITION(graph->nodes[toId] && graph->nodes[fromId], "Init Graph Error!");

    arrayAdd(graph->nodes[toId]->preNodes, fromId);
    graph->nodes[fromId]->outlinkCount++;
    graph->edgeCount ++;

    return TRUE;
}


BackwardGraph *loadBackwardGraph(const char *filename, int nodeCount){
    BackwardGraph *graph;
    double totalTime = 0;
    int i;

    if(nodeCount == 0){
        nodeCount = countNode(filename);
    }

    logMsg("Start Loading Graph From File: %s.\n", filename);

    graph = createBackwardGraph(nodeCount);
    for(i = 0; i < nodeCount; i++){
        graph->nodes[graph->nodeCount++] = createBackwardNode();
    }

    loadGraphFile((void*)graph, filename, &backwardGraphLoader);

    // check dead ends
    logMsg("Checking Deadends...\n");
    for(i = 0; i < graph->nodeCount; i++){
        if(i % 100000 == 0 && i != 0){
            logMsg("Checked %d nodes. Dead Ends Count: %d\n", i, graph->deadends->length);
        }
        if(graph->nodes[i]->outlinkCount == 0){
            arrayAdd(graph->deadends, i);
        }
    }

    logMsg("Finish Loading Graph[V = %d, E = %d, D = %d]. Total Time: %0.2lf sec.\n", 
            graph->nodeCount, graph->edgeCount, graph->deadends->length, totalTime);

    return graph;
}

BOOL canFinish(double *pre, double *rank, int length){
    int i;
    for(i = 0; i < length; i++){
        if(fabs(pre[i] - rank[i]) > fmin(1.0 / length / 100, LIMITATION)){
            return FALSE;
        }
    }
    return TRUE;
}

void powerIter(BackwardGraph *graph, double *pre, double *rank, double jumpProb){
    int i, j, index;
    double randomJumpValue = 0.0;
    double deadEndValue = 0.0;

    // copy and reset rank array
    for(i = 0; i < graph->nodeCount; i++){
        pre[i] = rank[i];
        rank[i] = 0.0;
    }

    for(i = 0; i < graph->nodeCount; i++){
        randomJumpValue += jumpProb * pre[i] / graph->nodeCount;
    }

    for(i = 0; i < graph->deadends->length; i++){
        deadEndValue += (1 - jumpProb) * pre[arrayGet(graph->deadends, i)] / graph->nodeCount;
    }

    for(i = 0; i < graph->nodeCount; i++){
        for(j = 0; j < graph->nodes[i]->preNodes->length; j++){
            index = arrayGet(graph->nodes[i]->preNodes, j);
            rank[i] += (1 - jumpProb) / graph->nodes[index]->outlinkCount * pre[index];
        }

        rank[i] += randomJumpValue;
        rank[i] += deadEndValue;
    }
}

int prComparator(const void *a, const void *b){
    PRNode *node1 = (PRNode*)a;
    PRNode *node2 = (PRNode*)b;

    if(node2->pr > node1->pr){
        return 1;
    }else if(node2->pr < node1->pr){
        return -1;
    }else{
        return 0;
    }
}

PRNode *computePageRank(BackwardGraph *graph, double jumpProb){
    double *rank;
    double *pre;
    PRNode *prnodes;

    double initValue = 1.0 / graph->nodeCount;
    int iterCount = 0;
    int i;
    clock_t begin, end;

    NEW_ARRAY(rank, double, graph->nodeCount);
    NEW_ARRAY(pre, double, graph->nodeCount);

    logMsg("Start Computing PageRank...\n");

    for(i = 0; i < graph->nodeCount; i++){
        rank[i] = initValue;
    }

    while(!canFinish(pre, rank, graph->nodeCount) && iterCount < MAX_ITER_COUNT){
        logMsg("Start Computing Power Iteration(%d)....", iterCount);
        begin = clock();
        powerIter(graph, pre, rank, jumpProb);
        end = clock();
        logMsg("Finish. Total Time: %0.2lf sec.\n", (double)(end - begin) / CLOCKS_PER_SEC);

        iterCount ++;
    }
    free(pre);

    logMsg("Finish Computing PageRank.\nStart Sorting Nodes by PageRank Value...");
    NEW_ARRAY(prnodes, PRNode, graph->nodeCount);
    for(i = 0; i < graph->nodeCount; i++){
        prnodes[i].index = i;
        prnodes[i].pr = rank[i];
    }
    free(rank);

    qsort(prnodes, graph->nodeCount, sizeof(PRNode), prComparator);
    logMsg("Finish Sorting.\n");

    return prnodes;
}