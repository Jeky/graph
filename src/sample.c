#include "sample.h"

int *randomNodeSample(int nodeCount, int count){
    int i;
    int *sample;
    srand(time(NULL));
    clock_t begin, end;
    begin = clock();

    NEW_ARRAY(sample, int, count);

    logMsg("Starting Sampling Graph(V = %d), using Random Node Sampling Method...Sample Count: %d\n", nodeCount, count);

    for(i = 0; i < count; i++){
        sample[i] = randInt(nodeCount);
    }

    end = clock();
    logMsg("Finish Sampling Graph. Total Time: %0.2lf\n", (double)(end - begin) / CLOCKS_PER_SEC);

    return sample;
}

BOOL edgeLoader(void *graph, int lineIndex, int fromId, int toId){
    Edge *edges = (Edge*) graph;

    edges[lineIndex].fromId = fromId;
    edges[lineIndex].toId = toId;

    return TRUE;
}

Edge *randomEdgeSample(const char *input, int edgeCount, int count){
    Edge *edges, *sample;
    int i, index;
    clock_t begin, end;
    double totalTime;
    begin = clock();

    NEW_ARRAY(edges, Edge, edgeCount);
    NEW_ARRAY(sample, Edge, count);

    logMsg("Starting Sampling Graph(E = %d), using Random Edge Sampling Method...Sample Count: %d\n", edgeCount, count);

    totalTime = loadGraphFile(edges, input, &edgeLoader);

    for(i = 0; i < count; i++){
        index = randInt(edgeCount);
        sample[i].fromId = edges[index].fromId;
        sample[i].toId = edges[index].toId;
    }

    end = clock();
    logMsg("Finish Sampling Graph. Total Time: %0.2lf sec.\n", (double)(end - begin) / CLOCKS_PER_SEC);

    free(edges);

    return sample;
}


BOOL forwardGraphLoader(void *graph, int lineIndex, int fromId, int toId){
    ForwardGraph *g = (ForwardGraph*)graph;
    arrayAdd(g->nodes[fromId], toId);

    return TRUE;
}

Step *randomWalkSample(char *input, int nodeCount, double jp, int count){
    ForwardGraph *graph;
    Step *sample;
    int i, index;
    clock_t begin, end;
    double totalTime;
    begin = clock();

    logMsg("Starting Sampling Graph(V = %d), using Random Walk Sampling Method...Sample Count: %d\n", nodeCount, count);

    // init graph
    NEW(graph, ForwardGraph);
    NEW_ARRAY(graph->nodes, Array*, nodeCount);
    graph->nodeCount = nodeCount;
    for(i = 0; i < nodeCount; i++){
        graph->nodes[i] = createArray();
    }

    // init steps
    NEW_ARRAY(sample, Step, count);

    // load graph
    totalTime = loadGraphFile(graph, input, &forwardGraphLoader);

    // sample
    // select first step
    index = randInt(nodeCount);
    sample[0].index = index;
    sample[0].tag = JUMP;

    for(i = 1; i < count; i++){
        if(uniRand() < jp){ // jump
            index = randInt(nodeCount);
            sample[i].index = index;
            sample[i].tag = JUMP;
        }else{
            if(graph->nodes[index]->length == 0){ // jump when dead end
                index = randInt(nodeCount);
                sample[i].index = index;
                sample[i].tag = JUMP;
            }else{ // walk
                index = arrayGet(graph->nodes[index], randInt(graph->nodes[index]->length));
                sample[i].index = index;
                sample[i].tag = WALK;
            }
        }
    }

    // destroy graph
    for(i = 0; i < nodeCount; i++){
        destroyArray(graph->nodes[i]);
    }
    free(graph->nodes);
    free(graph);

    end = clock();
    logMsg("Finish Sampling Graph. Total Time: %0.2lf sec.\n", (double)(end - begin) / CLOCKS_PER_SEC);

    return sample;
}























