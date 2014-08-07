#ifndef _PAGERANK_H_
#define _PAGERANK_H_

#include "utils.h"

#define BUF_SIZE 100

double loadGraphFile(void *graph, const char *filename, BOOL (*lineHandleFun)(void*,int,int,int));

#endif