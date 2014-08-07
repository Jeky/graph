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
            printf("read %d lines\n", lineCounter);
        }
        lineCounter += 1;
    }

    fclose(fp);
    end = clock();

    return (double)(end - begin) / CLOCKS_PER_SEC;
}

