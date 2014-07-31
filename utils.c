#include "utils.h"


Array *createArray(){
    Array *array = NEW(Array);

    CHECK_CONDITION(array != NULL, "Memory Allocation of Array Failed!");

    array->length = 0;
    array->values = NEW_ARRAY(int, DEFAULT_ARRAY_SIZE);
    array->capacity = DEFAULT_ARRAY_SIZE;

    CHECK_CONDITION(array->values != NULL, "Memory Allocation of Array Failed!");

    return array;
}

void destroyArray(Array *array){
    free(array->values);
    free(array);
}

void encapsulateArray(Array *array){
    int *tmp = array->values;
    int i = 0;

    array->capacity *= 2;
    array->values = NEW_ARRAY(int, array->capacity);
    CHECK_CONDITION(array->values != NULL, "Memory Allocation of Array Failed!");

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
