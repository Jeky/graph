#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

#define CHECK_CONDITION(condition, message) assert(condition && message);
#define NEW(var, type)  do{\
                            var = (type*)malloc(sizeof(type)); \
                            CHECK_CONDITION(var != NULL, "Memory Allocation Failed!\n");\
                        }while(0);
#define NEW_ARRAY(var, type, size)  do{\
                                        var = (type*)malloc(sizeof(type) * size); \
                                        CHECK_CONDITION(var != NULL, "Memory Allocation Failed!\n");\
                                    }while(0);

#define BOOL char
#define TRUE 1
#define FALSE 0

#define DEFAULT_ARRAY_SIZE 128

typedef struct _array{
    int length;
    int *values;
    int capacity;
} Array;

/**
 * Array functions
 */
Array *createArray();

Array *createArrayWithCapacity(int capacity);

void destroyArray(Array *array);

void arrayAdd(Array *array, int val);

int arrayGet(Array *array, int index);

// log functions
static BOOL logFlag = TRUE;

void setOutput(BOOL isOutput);

void logMsg(char *format, ...);

// random functions
double uniRand();

int randInt(int max);

#endif