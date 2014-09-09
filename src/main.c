
#include "sample.h"
#define COUNT 1000000
#define NODE_COUNT 42000000
#define DATA_PATH "/Volumes/Time Machine/jeky/twitter/twitter-encode.graph"

ForwardGraph *loadForwardGraph(char *input, int nodeCount){
    ForwardGraph *graph;
    int i;

    // init graph
    NEW(graph, ForwardGraph);
    NEW_ARRAY(graph->nodes, Array*, nodeCount);
    graph->nodeCount = nodeCount;
    for(i = 0; i < nodeCount; i++){
        graph->nodes[i] = createArray();
    }

    // load graph
    loadGraphFile(graph, input, &forwardGraphLoader);

    return graph;
}

void logSample(FILE *fp, int index, int jumpTag){
    fprintf(fp, "%d\t%d\n", index, jumpTag);
}

void longRandomWalkSample(ForwardGraph *graph, double jp, int count, FILE *fp){
    int i, index;
    // sample
    // select first step
    index = randInt(graph->nodeCount);
    logSample(fp, index, JUMP);

    for(i = 1; i < count; i++){
        if(uniRand() < jp){ // jump
            index = randInt(graph->nodeCount);
            logSample(fp, index, JUMP);
        }else{
            if(graph->nodes[index]->length == 0){ // jump when dead end
                index = randInt(graph->nodeCount);
                logSample(fp, index, JUMP);
            }else{ // walk
                index = arrayGet(graph->nodes[index], randInt(graph->nodes[index]->length));
                logSample(fp, index, WALK);
            }
        }
    }
}

void destroyForwardGraph(ForwardGraph *graph){
    int i;
    for(i = 0; i < graph->nodeCount; i++){
        destroyArray(graph->nodes[i]);
    }
    free(graph->nodes);
    free(graph);

}

int main(){
    ForwardGraph *graph = loadForwardGraph(DATA_PATH, NODE_COUNT);
    int i = 0, j;
    FILE *fp;
    char buffer[100];

    for(i = 1; i <= 20; i++){
        sprintf(buffer, "/Volumes/Time Machine/jeky/twitter/rw/%d", i);
        fp = fopen(buffer, "w");
        for(j = 0; j < 1000; j++){
            printf("Sampling...JP = %0.2f, COUNT = %d\n", i * 0.01, j);
            longRandomWalkSample(graph, i * 0.01, COUNT, fp);
        }
        fclose(fp);
    }

    destroyForwardGraph(graph);

    return 0;
}


