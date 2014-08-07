#include "sample.h"

int randInt(int max){
	double r = (double)rand() / RAND_MAX * max;
	return (int)r;
}

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

Step *randomWalkSample(char *input, int nodeCount, double jp, int count){
	return NULL;
}