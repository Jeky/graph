#include "utils.h"


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