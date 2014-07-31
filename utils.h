#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

#define NEW(type) (type*)malloc(sizeof(type));
#define NEW_ARRAY(type, size) (type*)malloc(sizeof(type) * size)

#define DEFAULT_ARRAY_SIZE 128

#define CHECK_CONDITION(condition, message) assert(condition && message);

typedef struct _array{
    int length;
    int *values;
    int capacity;
} Array;

/**
 * Array functions
 */
Array *createArray();

void destroyArray(Array *array);

void arrayAdd(Array *array, int val);

#endif