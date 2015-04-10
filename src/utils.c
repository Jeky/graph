#include "utils.h"
#include <stdarg.h>

Array *createArrayWithCapacity(int capacity){
    Array *array;
    NEW(array, Array);

    array->length = 0;
    array->capacity = capacity;
    NEW_ARRAY(array->values, int, array->capacity);

    return array;
}

Array *createArray(){
    return createArrayWithCapacity(DEFAULT_ARRAY_SIZE);
}

void destroyArray(Array *array){
    free(array->values);
    free(array);
}

void encapsulateArray(Array *array){
    int *tmp = array->values;
    int i = 0;

    array->capacity += DEFAULT_ARRAY_SIZE;
    NEW_ARRAY(array->values, int, array->capacity);

    for(i = 0; i < array->length; i++){
        array->values[i] = tmp[i];
    }

    free(tmp);
}

void arrayAdd(Array *array, int val){
    if(array->length == array->capacity){
        encapsulateArray(array);
    }

    array->values[array->length++] = val;
}

int arrayGet(Array *array, int index){
    CHECK_CONDITION(index < array->length, "Index Out of Bound.");

    return array->values[index];
}


double uniRand(){
    return (double)rand() / RAND_MAX;
}

int randInt(int max){
    double r =  uniRand() * max;
    return (int)r;
}


void setOutput(BOOL isOutput){
    logFlag = isOutput;
}

void logMsg(char *format, ...){
    va_list argptr;
    va_start(argptr, format);
    if(logFlag){
        vfprintf(stdout, format, argptr);
    }
    va_end(argptr);
}