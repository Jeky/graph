#include "graph.h"

Array *createArray(){
	Array *array = NEW(Array);

	array->length = 0;
	array->values = NEW_ARRAY(int, DEFAULT_ARRAY_SIZE);
	array->capacity = DEFAULT_ARRAY_SIZE;

	return array;
}

void destroyArray(Array *array){
	free(array->values);
	free(array);
}

void encapsulate(Array *array){
	int *tmp = array->values;
	int i = 0;

	array->capacity *= 2;
	array->values = NEW_ARRAY(int, array->capacity);

	for(i = 0; i < array->length; i++){
		array->values[i] = tmp[i];
	}

	free(tmp);
}

void arrayAdd(Array *array, int val){
	if(array->length == array->capacity){
		encapsulate(array);
	}

	array->values[array->length++] = val;
}


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

void addNode(Graph *graph, Node *node){

}








