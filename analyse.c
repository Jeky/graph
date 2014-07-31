#include "analyse.h"
#include <math.h>

BOOL canFinish(double *pre, double *rank, int length){
    int i;
    for(i = 0; i < length; i++){
        if(fabs(pre[i] - rank[i]) > fmin(1.0 / length / 2, LIMITATION)){
            return FALSE;
        }
    }
    return TRUE;
}

void powerIter(Graph *graph, double *pre, double *rank, double jumpProb){
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

PRNode *computePageRank(Graph *graph, double jumpProb){
    double *rank;
    double *pre;
    PRNode *prnodes;

    double initValue = 1.0 / graph->nodeCount;
    int iterCount = 0;
    int i;
    clock_t begin, end;

    NEW_ARRAY(rank, double, graph->nodeCount);
    NEW_ARRAY(pre, double, graph->nodeCount);

    printf("Start Computing PageRank...\n");

    for(i = 0; i < graph->nodeCount; i++){
        rank[i] = initValue;
    }

    while(!canFinish(pre, rank, graph->nodeCount) && iterCount < MAX_ITER_COUNT){
        printf("Start Computing Power Iteration(%d)....", iterCount);
        begin = clock();
        powerIter(graph, pre, rank, jumpProb);
        end = clock();
        printf("Finish. Total Time: %0.2lf sec.\n", (double)(end - begin) / CLOCKS_PER_SEC);

        iterCount ++;
    }
    free(pre);

    printf("Finish Computing PageRank.\nStart Sorting Nodes by PageRank Value...");
    NEW_ARRAY(prnodes, PRNode, graph->nodeCount);
    for(i = 0; i < graph->nodeCount; i++){
        prnodes[i].index = i;
        prnodes[i].pr = rank[i];
    }
    free(rank);

    qsort(prnodes, graph->nodeCount, sizeof(PRNode), prComparator);
    printf("Finish Sorting.\n");

    return prnodes;
}